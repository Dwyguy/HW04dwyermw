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
		if(e->x <= r->key->x)
			r->left = insert(e, r->left, !isXlevel);
		else
			r->right = insert(e, r->right, !isXlevel);
	}
	else
	{
		if(e->y <= r->key->y)
			r->left = insert(e, r->left, !isXlevel);
		else
			r->right = insert(e, r->right, !isXlevel);
	}

	return r;
}

Entry* Node::search(Entry* key, Node* r, bool isXlevel)
{
	if(r == NULL)
		return NULL;

	if(isXlevel)
	{
		if(key->x <= r->key->x)
		{
			if(r->left == NULL) // If there is no left node, the current node is the closest location
				return r->key;
			else
				return search(key, r->left, !isXlevel);
		}
		else
		{
			if(r->right == NULL)
				return r->key;
			else
				return search(key, r->right, !isXlevel);
		}
	}
	else
	{
		if(key->y <= r->key->y)
		{
			if(r->right == NULL)
				return r->key;
			else
				return search(key, r->left, !isXlevel);
		}
		else
		{
			if(r->right == NULL)
				return r->key;
			else
				return search(key, r->right, !isXlevel);
		}
	}


	return NULL;
}