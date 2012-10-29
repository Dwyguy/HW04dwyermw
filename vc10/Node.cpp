#include "Node.h"


Node::Node(Entry* e)
{
	key = e;
	left = NULL;
	right = NULL;
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
		{
			if(r->left != NULL)
				r->left = insert(e, r->left, !isXlevel);
			else
				r->left = new Node(e);
		}
		else if(e->x > r->key->x)
		{
			if(r->right != NULL)
				r->right = insert(e, r->right, !isXlevel);
			else
				r->right = new Node(e);
		}
	}
	else
	{
		if(e->y <= r->key->y)
		{
			if(r->left != NULL)
				r->left = insert(e, r->left, !isXlevel);
			else
				r->left = new Node(e);
		}
		else if(e->y > r->key->y)
		{
			if(r->right != NULL)
				r->right = insert(e, r->right, !isXlevel);
			else
				r->right = new Node(e);
		}
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
				search(key, r->left, !isXlevel);
		}
		else
		{
			if(r->right == NULL)
				return r->key;
			else
				search(key, r->right, !isXlevel);
		}
	}
	else
	{
		if(key->y <= r->key->y)
		{
			if(r->right == NULL)
				return r->key;
			else
				search(key, r->left, !isXlevel);
		}
		else
		{
			if(r->right == NULL)
				return r->key;
			else
				search(key, r->right, !isXlevel);
		}
	}


	return NULL;
}

Node* Node::next(Entry* key, Node* r)
{
	if(r == NULL)
		return NULL;
	else if(key > r->key)
		return next(key, r->right);
	else
	{
		Node* temp = next(key, r->left);
		if(temp == NULL)
			return r;
		else
			return temp;
	}
}

Node* Node::previous(Entry* key, Node* r)
{
	if(r == NULL)
		return NULL;
	else if(key < r->key)
		return previous(key, r->left);
	else
	{
		Node* temp = previous(key, r->right);
		if(temp == NULL)
			return r;
		else
			return temp;
	}
}