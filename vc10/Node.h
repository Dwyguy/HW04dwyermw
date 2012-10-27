#pragma once
#include "Starbucks.h"

class Node
{
public:
	Node(Entry* e);
	~Node(void);
	Node* insert(Entry* e, Node* r, bool isXlevel);

private:
	Entry* key;
	Node* left;
	Node* right;
};

