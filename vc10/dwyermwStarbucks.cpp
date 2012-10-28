#include "dwyermwStarbucks.h"
#include "Node.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace std;

dwyermwStarbucks::dwyermwStarbucks()
{
}


dwyermwStarbucks::~dwyermwStarbucks(void)
{
}

void dwyermwStarbucks::build(Entry* c, int n)
{
	vector<Entry> storage;
	storage.push_back(n);

	// Convert from array back to vector.  This step seems useless,
	// but it is much easier to remove duplicates while the data is in
	// vector form.
	for(int x = 0; x < n; x++)
		c[x] = storage[x];

	// Check for duplicate locations.  A duplicate location is defined as
	// both the x and y values of the compared locations being within
	// 0.0001 of one another
	for(int a = 0; a < storage.size(); a++)
		for(int b = a + 1; b < storage.size(); b++)
			if(abs(storage[a].x - storage[b].x) <= 0.0001)
				if(abs(storage[a].y - storage[b].y) <= 0.0001)
					storage.erase(a);

	// Shuffles vector to make it random
	std::random_shuffle(storage.begin(), storage.end());
	Entry* locs = new Entry[storage.size()];
	
	// Copies all values from the vector to the array
	for(int y = 0; y < storage.size(); y++)
		locs[y] = storage[y];
	
	
	// Building the K-D tree
	for(int p = 0; p < storage.size(); p++)
	{
		root = new Node(&locs[p]);
		root->insert(&locs[p], root, true);
	}

}

Entry* dwyermwStarbucks::getNearest(double x, double y)
{
	
}
