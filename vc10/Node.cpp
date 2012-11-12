/**
* @file Node.cpp
* CSE 274 - Fall 2012
*
* @author Matthew Dwyer
* @date 10/29/2012
*
* @note This file is (c) 2012. It is licensed under the
* CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
* which means you are free to use, share, and remix it as long as you
* give attribution. Commercial uses are allowed.
*
*/

#include "Node.h"

Node::Node(Entry* e)
{
	key = e;
	left = NULL;
	right = NULL;
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
	Entry* closest;
	if(r == NULL)
		return NULL;

	if(key->x == r->key->x && key->y == r->key->y)
	{
		finalEntry = r;
		return r->key;
	}

	if(isXlevel)
	{
		if(key->x <= r->key->x)
		{
			if(r->left == NULL) // If there is no left node, the current node is the closest location
			{
				closest = r->key;
				finalEntry = r;
			}
			else
			{
				parent = r;
				closest = search(key, r->left, !isXlevel);
			}
		}
		else
		{
			if(r->right == NULL)
			{
				closest = r->key;
				finalEntry = r;
			}
			else
			{
				parent = r;
				closest = search(key, r->right, !isXlevel);
			}
		}
	}
	else
	{
		if(key->y <= r->key->y)
		{
			if(r->left == NULL)
			{
				closest = r->key;
				finalEntry = r;
			}
			else
			{
				parent = r;
				closest = search(key, r->left, !isXlevel);
			}
		}
		else
		{
			if(r->right == NULL)
			{
				closest = r->key;
				finalEntry = r;
			}
			else
			{
				parent = r;
				closest= search(key, r->right, !isXlevel);
			}
		}
	}

	return closest;
}

Node* Node::next(Node* r, bool firstTime)
{
	Node* next_node;

	if(r->right == NULL && r->left != NULL)
		return parent;
	// This decreases accuracy, however, I ran out of time to implement
	// a good work around.  This is a quick fix that allows problems to
	// be bypassed.
	if(r->right == NULL && r->left == NULL)
		return parent;

	if(r->right->left != NULL && firstTime)
		next_node = next(r->right, false);
	else if(r->left != NULL)
		next_node = next(r->left, false);
	else
		next_node = r->right;

	return next_node;

	// Original method, which did not work well at all
	/*if(r == NULL)
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
	}*/
}

Node* Node::previous(Node* r, bool firstTime)
{
	Node* prev_node;

	if(r->left == NULL && r->right != NULL)
		return parent;
	// This decreases accuracy, however, I ran out of time to implement
	// a good work around.  This is a quick fix that allows problems to
	// be bypassed.
	if(r->left == NULL && r->right == NULL)
		return parent;

	if(r->left->right != NULL && firstTime)
		prev_node = next(r->left, false);
	else if(r->right != NULL)
		prev_node = next(r->right, false);
	else
		prev_node = r->left;

	return prev_node;

	// Original method, which sort of worked
	/*if(r == NULL)
		return NULL;
	else if(key < r->key)
		return r;//return previous(key, r->left);
	else
	{
		Node* temp = previous(key, r->right);
		if(temp == NULL)
			return r;
		else
			return temp;
	}*/
}

Node* Node::getFinalEntry()
{
	return finalEntry;
}

