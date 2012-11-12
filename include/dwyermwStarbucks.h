#pragma once
#include <string>
#include "Starbucks.h"
#include "Node.h"
using namespace std;


class dwyermwStarbucks : public Starbucks
{
public:
	/**
	Constructs a new dwyermwStarbucks object
	*/
	dwyermwStarbucks();

	/**
	Builds a binary (k-d) tree data structure to store locations of
	Starbucks.  The locations are pointed to by the Entry* object.
	@param c - A pointer to the array of Starbucks locations
	@param n - The size of the Starbucks locations array
	*/
	void build(Entry* c, int n);

	/**
	Gets the nearest Starbucks location to a given point by searching
	a binary tree and returning the closest entry it can find.
	@param x - the x coordinate of the location
	@param y - the y coordinate of the location
	*/
	Entry* getNearest(double x, double y);

	// The root node to the binary tree structure
	Node* root;
	
	//
	Entry* locs;
	int locsLen;

	int getlocsLen();


};

