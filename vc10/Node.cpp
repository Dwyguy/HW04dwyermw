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
	if(isXlevel)
	{
		if(e->x < r->key->x)
			r->left = insert(e, r->left, !isXlevel);
		else
			r->right = insert(e, r->right, !isXlevel);
	}
	else
	{
		if(e->y < r->key->y)
			r->left = insert(e, r->left, !isXlevel);
		else
			r->right = insert(e, r->right, !isXlevel);
	}

	return r;
}