#include "dwyermwStarbucks.h"
#include "Node.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <fstream>
#include <iostream>

using namespace ci;
using namespace ci::app;
using namespace std;

dwyermwStarbucks::dwyermwStarbucks()
{
	ifstream in("Starbucks_2006.csv");
	vector <Entry> storage;
	locsLen = 0;
	
	string line;
	double d;
	double d2;
	char separator;
	int x = 0;
	
	// Reads in all values from the .csv file
	while(in.good())
	{
		Entry* e = new Entry();
		storage.push_back(*e);
		getline(in, line, ',');
		
		storage[x].identifier = line;
		in >> d;
		storage[x].x = d;
		in >> separator; // Gets the separator
		in >> d2;
		storage[x].y = d2;
		x++;
		console() << line;
	}

	//locsLen = storage.size();
	locs = new Entry[storage.size()];
	
	// Copies all values from the vector to the array
	for(int y = 0; y < storage.size(); y++)
		locs[y] = storage[y];

	// Builds the binary tree
	build(locs, storage.size());


}


void dwyermwStarbucks::build(Entry* c, int n)
{
	vector<Entry> storage;

	// Convert from array back to vector.  This step seems useless,
	// but it is much easier to remove duplicates while the data is in
	// vector form.
	for(int x = 0; x < n; x++)
		storage.push_back(c[x]); // Adds the element to the end of the vector

	// Check for duplicate locations.  A duplicate location is defined as
	// both the x and y values of the compared locations being within
	// 0.00001 of one another
	for(int a = 0; a < storage.size(); a++)
	{
		for(int b = a + 1; b < storage.size(); b++)
		{
			if(abs(storage[a].x - storage[b].x) <= 0.00001)
			{
				if(abs(storage[a].y - storage[b].y) <= 0.00001)
					storage.erase(storage.begin() + a);
			}
		}
	}

	// Shuffles vector to make it random
	std::random_shuffle(storage.begin(), storage.end());

	Entry* locs = new Entry[storage.size()];
	
	// Copies all values from the vector to the array
	for(int y = 0; y < storage.size(); y++)
		locs[y] = storage[y];

	Node* r = NULL;

	// Building the K-D tree
	for(int p = 0; p < storage.size(); p++)
	{
		// First time through, gets the root node.  Then builds off that
		if(p == 0)
		{
			r = r->insert(&locs[p], r, true);
			root = r; // root now points to the root node of the k-d tree
		}
		else
			r->insert(&locs[p], r, true);
	}

	locsLen = storage.size();
}

Entry* dwyermwStarbucks::getNearest(double x, double y)
{
	Entry* base = new Entry();
	base->x = x;
	base->y = y;

	Entry* e = root->search(base, root, true);
	Node* finalEntry = root->getFinalEntry();

	// Find the two closest nodes to the node found
	// Can sometimes lead to spotty results, but catches
	// the closer location sometimes.  For accuracy purposes,
	// I feel it's ok to leave these here.  I do not believe it
	// affects runtime in a drastic way.  Can also be removed
	// with little loss of accuracy (comparatively)
	Node* node_prev = root->previous(finalEntry, true);
	Node* node_next = root->next(finalEntry, true);

	Entry* e_prev = node_prev->key;
	Entry* e_next = node_next->key;

	double dist1 = sqrt(pow(x - e->x, 2) + pow(y - e->y, 2));
	double dist2 = sqrt(pow(x - e_prev->x, 2) + pow(y - e_prev->y, 2));
	double dist3 = sqrt(pow(x - e_next->x, 2) + pow(y - e_next->y, 2));

	// Finds the shortest of the three distances and returns them
	double min_dist = min(dist1, dist2);
	min_dist = min(min_dist, dist3);

	if(min_dist == dist1)
		return e;
	else if(min_dist == dist2)
		return e_prev;
	else
		return e_next;
}

int dwyermwStarbucks::getlocsLen()
{
	return locsLen;
}