#include "tree_iterators.hpp"

namespace ft {

template <typename T>
static tree_node<T>*
_tree_increment(tree_node<T>* x)
{
	if (x->right != 0)
	{
		x = x->right;
		while (x->left != 0)
			x = x->left;
	}
	else
	{
		tree_node<T>* y = x->parent;
		while (x == y->right)
		{
			x = y;
			y = y->parent;
		}
		if (x->right != y)
			x = y;
	}
	return x;
}

template <typename T>
tree_node<T>*
tree_increment(tree_node<T>* x)
{ return _tree_increment(x); }

template <typename T>
const tree_node<T>*
tree_increment(const tree_node<T>* x)
{ return _tree_increment(const_cast<tree_node<T>*>(x)); }

template <typename T>
static tree_node<T>*
_tree_decrement(tree_node<T>* x)
{
	if (x->color == red && x->parent->parent == x)
		x = x->right;
	else if (x->left != 0)
	{
		tree_node<T>* y = x->left;
		while (y->right != 0)
			y = y->right;
		x = y;
	}
	else
	{
		tree_node<T>* y = x->parent;
		while (x == y->left)
		{
			x = y;
			y = y->parent;
		}
		x = y;
	}
	return x;
}

template <typename T>
tree_node<T>*
tree_decrement(tree_node<T>* x)
{ return _tree_decrement(x); }

template <typename T>
const tree_node<T>*
tree_decrement(const tree_node<T>* x)
{ return _tree_decrement(const_cast<tree_node<T>*>(x)); }

template <typename T>
static void
_tree_rotate_left(tree_node<T>* const x, tree_node<T>*& root)
{
	tree_node<T>* const y = x->right;

	x->right = y->left;
	if (y->left != 0)
		y->left->parent = x;
	y->parent = x->parent;

	if (x == root)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

template <typename T>
static void
_tree_rotate_right(tree_node<T>* const x, tree_node<T>*& root)
{
	tree_node<T>* const y = x->left;

	x->left = y->right;
	if (y->right != 0)
		y->right->parent = x;
	y->parent = x->parent;

	if (x == root)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;
	y->right = x;
	x->parent = y;
}

template <typename T>
void
tree_insert_and_rebalance(const bool insert_left,
	tree_node<T>* x, tree_node<T>* p, tree_node<T>& head)
{
	tree_node<T>*& root = head.parent;

	/* init variables in new node to insert */
	x->color = red;
	x->parent = p;
	x->left = 0;
	x->right = 0;

	/* insert */
	if (insert_left)
	{
		p->left = x; // also makes leftmost = x when p == &head

		if (p == &head)
		{
			head.parent = x;
			head.right = x;
		}
		else if (p == head.left)
			head.left = x; // keep leftmost pointing to min node
	}
	else
	{
		p->right = x;
		
		if (p == head.right)
			head.right = x; // keep leftmost pointing to max node
	}
	/* rebalance */
	while (x != root && x->parent->color == red)
	{
		tree_node<T>* const xpp = x->parent->parent;

		if (x->parent == xpp->left)
		{
			tree_node<T>* const y = xpp->right;
			if (y && y->color == red)
			{
				x->parent->color = black;
				y->color = black;
				xpp->color = red;
				x = xpp;
			}
			else
			{
				if (x == x->parent->right)
				{
					x = x->parent;
					_tree_rotate_left(x, root);
				}
				x->parent->color = black;
				xpp->color = red;
				_tree_rotate_right(xpp, root);
			}
		}
		else
		{
			tree_node<T>* const y = xpp->left;
			if (y)
			{
				x->parent->color = black;
				y->color = black;
				xpp->color = red;
				x = xpp;
			}
			else
			{
				if (x == x->parent->left)
				{
					x = x->parent;
					_tree_rotate_right(x, root);
				}
				x->parent->color = black;
				xpp->color = red;
				_tree_rotate_left(xpp, root);
			}
		}
	}
	root->color = black;
}

template <typename T>
tree_node<T>*
tree_rebalance_for_erase(tree_node<T>* const z, tree_node<T>& head)
{
	tree_node<T>*& root = head.parent;
	tree_node<T>*& leftmost = head.left;
	tree_node<T>*& rightmost = head.right;
	tree_node<T>* y = z;
	tree_node<T>* x = 0;
	tree_node<T>* xp = 0;

	if (y->left == 0) // z has at most one child
		x = y->right; // x might be null
	else
	{
		if (y->right == 0) // z has exactly one child (left)
			x = y->left; // x is not null
		else // z has two children
		{
			y = y->right; // z's successor
			while (y->left != 0)
				y = y->left;
			x = y->right; // x might be null
		}
	}
	if (y != z) // relink y (successor) in place of z
	{
		z->left->parent = y;
		y->left = z->left;
		if (y != z->right)
		{
			xp = y->parent;
			if (x)
				x->parent = y->parent;
			y->parent->left = x; // y must be left child
			y->right = z->right;
			z->right->parent = y;
		}
		else
			xp = y;
		if (root == z)
			root = y;
		else if (z->parent->left == z)
			z->parent->left = y;
		else
			z->parent->right = y;
		y->parent = z->parent;
		{
			tree_color tmp = y->color;
			y->color = z->color;
			z->color = tmp;
		}
		y = z; // y now points to node to be deleted
	}
	else // y == z
	{
		xp = y->parent;
		if (x)
			x->parent = y->parent;
		if (root == z)
			root = x;
		else
		{
			if (z->parent->left == z)
				z->parent->left = x;
			else
				z->parent->right = x;
		}
		if (leftmost == z)
		{
			if (z->right == 0) // z->left must be null also
				leftmost = z->parent; // makes leftmost head if z == root
			else
				leftmost = tree_node<T>::minimum(x);
		}
		if (rightmost == z)
		{
			if (z->left == 0) // z->right must be null also
				rightmost = z->parent; // makes rightmost head if z == root
			else
				rightmost = tree_node<T>::maximum(x);
		}
	}
	if (y->color != red)
	{
		while (x != root && (x == 0 || x->color == black))
		{
			if (x == xp->left)
			{
				tree_node<T>* w = xp->right;
				if (w->color == red)
				{
					w->color = black;
					xp->color = red;
					_tree_rotate_left(xp, root);
					w = xp->right;
				}
				if ((w->left == 0 || w->left->color == black)
					&& (w->right == 0 || w->right->color == black))
				{
					w->color = red;
					x = xp;
					xp = xp->parent;
				}
				else
				{
					if (w->right == 0 || w->right->color == black)
					{
						w->left->color = black;
						w->color = red;
						_tree_rotate_right(w, root);
						w = xp->right;
					}
					w->color = xp->color;
					xp->color = black;
					if (w->right)
						w->right->color = black;
					_tree_rotate_left(xp, root);
					break ;
				}
			}
			else // same as above, with right <-> left
			{
				tree_node<T>* w = xp->left;
				if (w->color == red)
				{
					w->color = black;
					xp->color = red;
					_tree_rotate_right(xp, root);
					w = xp->left;
				}
				if ((w->right == 0 || w->right->color == black)
					&& (w->left == 0 || w->left->color == black))
				{
					w->color = red;
					x = xp;
					xp = xp->parent;
				}
				else
				{
					if (w->left == 0 || w->left->color == black)
					{
						w->right->color = black;
						w->color = red;
						_tree_rotate_left(w, root);
						w = xp->left;
					}
					w->color = xp->color;
					xp->color = black;
					if (w->left)
						w->left->color = black;
					_tree_rotate_right(xp, root);
					break ;
				}
			}
		}
		if (x)
			x->color = black;
	}
	return y;
}

}; // ft::
