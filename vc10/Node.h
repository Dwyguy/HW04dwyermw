#pragma once
#include "Starbucks.h"

class Node
{
public:
	Node(Entry* e);
	~Node(void);
	Node* insert(Entry* e, Node* r, bool isXlevel);
	Entry* search(Entry* key, Node* r, bool isXlevel);
	Node* next(Entry* key, Node* r);
	Node* previous(Entry* key, Node* r);

private:
	Entry* key;
	Node* left;
	Node* right;
};

