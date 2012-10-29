#pragma once
#include "Starbucks.h"

class Node
{
public:
	/**
	Constructs a new Node with an Entry*.
	@param e - An Entry held within the Node
	*/
	Node(Entry* e);

	/**
	Inserts a node into the binary tree during the building phase.
	This method is also recursive.
	@param e - Used to compare coordinates to see where the next Node
		is placed in the tree
	@param r - The current node to be placed
	@param isXlevel - Boolean to see if the x or y value is going to be compared
	@return - The inserted node
	*/
	Node* insert(Entry* e, Node* r, bool isXlevel);

	/**
	Finds the proper Starbucks location that is closest to the location specificed
	in the getNearest() method.  This method is recursive.
	@param key - used to compare coordinates to see which node will be compared next
	@param r - The current node being searched
	@param isXlevel - Boolean to see if the x or y value is going to be compared
	@return - The entry that is closest to the specificed coordinates in getNearest()
	*/
	Entry* search(Entry* key, Node* r, bool isXlevel);

	/**
	Finds the "next closest" node to the current one.  This method is recursive
	@param r - The current node
	@param firstTime - To do special cases if it is the first time through the method
	@return - The next closest node
	*/
	Node* next(Node* r, bool firstTime);

	/**
	Finds the "previous closest" node to the current one.  This method is recursive
	@param r - The current node
	@param firstTime - To do special cases if it is the first time through the method
	@return - The previous closest node
	*/
	Node* previous(Node* r, bool firstTime);

	/**
	Gets the final node to be returned as the best match for the coordinates
	specificed in the getNearest method
	*/
	Node* getFinalEntry();

	// The entry contained within each node
	Entry* key;

	// The left branch of the node
	Node* left;

	// The right branch of the node
	Node* right;

	// The last entry which will be received by the getNearest method
	Node* finalEntry;

	// The parent of the current node
	Node* parent;
};

