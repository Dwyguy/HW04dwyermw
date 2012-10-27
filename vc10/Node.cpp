#include "Node.h"


Node::Node(Entry* e)
{
	key = e;
}


Node::~Node(void)
{
}

Node* Node::insert(Entry* e, Node* r, bool isXlevel)
{
	if(r == NULL)
		return new Node(e);
	if(r->key == e)
		return r;
	if(e < r->key)
		r->left = insert(e, r->left, !isXlevel);
	else
		r->right = insert(e, r->right, !isXlevel);

	return r;
}