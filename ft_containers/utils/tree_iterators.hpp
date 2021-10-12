#ifndef TREE_ITERATORS_HPP
# define TREE_ITERATORS_HPP

# include "utils.hpp"

namespace ft {

/*   _  _         _       *\
**	| \| |___  __| |___   **
**	| .` / _ \/ _` / -_)  **
**	|_|\_\___/\__,_\___|  **
\*						  */

enum tree_color
{
	red = false,
	black = true
};

template <typename T>
struct tree_node
{
	typedef T								value_type;
	typedef tree_node<value_type>*			pointer;
	typedef const tree_node<value_type>*	const_pointer;

	tree_node()
	{}

	tree_node(const value_type& value)
	: value(value) {}

	tree_color	color;
	pointer		parent;
	pointer		left;
	pointer		right;
	value_type	value;

	static pointer
	minimum(pointer x)
	{
		while (x->left != 0)
			x = x->left;
		return x;
	}

	static const_pointer
	minimum(const_pointer x)
	{
		while (x->left != 0)
			x = x->left;
		return x;
	}

	static pointer
	maximum(pointer x)
	{
		while (x->right != 0)
			x = x->right;
		return x;
	}

	static const_pointer
	maximum(const_pointer x)
	{
		while (x->right != 0)
			x = x->right;
		return x;
	}
};

template <typename T>
tree_node<T>*
tree_increment(tree_node<T>* x);

template <typename T>
const tree_node<T>*
tree_increment(const tree_node<T>* x);

template <typename T>
tree_node<T>*
tree_decrement(tree_node<T>* x);

template <typename T>
const tree_node<T>*
tree_decrement(const tree_node<T>* x);

/*	 ___ _                _             *\
**	|_ _| |_ ___ _ _ __ _| |_ ___ _ _   **
**	 | ||  _/ -_) '_/ _` |  _/ _ \ '_|  **
**	|___|\__\___|_| \__,_|\__\___/_|    **
\*										*/

template <typename T>
class tree_iterator
: public ft::iterator<ft::bidirectional_iterator_tag, T>
{
	protected:
		tree_node<T>*	node;

	public:
		typedef T   				value_type;
		typedef T&					reference;
		typedef T*					pointer;

		typedef tree_iterator<T>	self;
		typedef tree_node<T>*		node_ptr;

		tree_iterator()
		: node() {}

		explicit
		tree_iterator(const node_ptr& x)
		: node(x) {}

		const node_ptr
		current() const
		{ return node; }

		reference
		operator*() const
		{ return static_cast<node_ptr>(node)->value; }

		pointer
		operator->() const
		{ return &static_cast<node_ptr>(node)->value; }

		self&
		operator++()
		{ node = tree_increment(node); return *this; }

		self
		operator++(int)
		{
			self tmp = *this;
			node = tree_increment(node);
			return tmp;
		}

		self&
		operator--()
		{ node = tree_decrement(node); return *this; }

		self
		operator--(int)
		{
			self tmp = *this;
			node = tree_decrement(node);
			return tmp;
		}

		bool
		operator==(const self& x) const
		{ return node == x.node; }

		bool
		operator!=(const self& x) const
		{ return node != x.node; }
};

/*	  ___             _     ___ _                _             *\
**	 / __|___ _ _  __| |_  |_ _| |_ ___ _ _ __ _| |_ ___ _ _   **
**	| (__/ _ \ ' \(_-<  _|  | ||  _/ -_) '_/ _` |  _/ _ \ '_|  **
**	 \___\___/_||_/__/\__| |___|\__\___|_| \__,_|\__\___/_|    **
\*															   */


template <typename T>
class tree_const_iterator
: public ft::iterator<ft::bidirectional_iterator_tag, T>
{
	protected:
		const tree_node<T>*	node;
	
	public:
		typedef T						value_type;
		typedef const T&				reference;
		typedef const T*				pointer;
	
		typedef tree_iterator<T>		iterator;
		
		typedef tree_const_iterator<T>	self;
		typedef const tree_node<T>*		node_ptr;

		tree_const_iterator()
		: node() {}

		explicit
		tree_const_iterator(node_ptr x)
		: node(x) {}

		tree_const_iterator(const iterator& it)
		: node(it.current()) {}

		const node_ptr
		current() const
		{ return node; }

		iterator
		_const_cast() const
		{
			return iterator(static_cast<typename iterator::node_ptr>
				(const_cast<typename iterator::node_ptr>(node)));
		}

		reference
		operator*() const
		{ return static_cast<node_ptr>(node)->value; }

		pointer
		operator->() const
		{ return &static_cast<node_ptr>(node)->value; }

		self&
		operator++()
		{ node = tree_increment(node); return *this; }

		self
		operator++(int)
		{
			self tmp = *this;
			node = tree_increment(node);
			return tmp;
		}

		self&
		operator--()
		{ node = tree_decrement(node); return *this; }

		self
		operator--(int)
		{
			self tmp = *this;
			node = tree_decrement(node);
			return tmp;
		}

		bool
		operator==(const self& x) const
		{ return node == x.node; }

		bool
		operator!=(const self& x) const
		{ return node != x.node; }
};

template <typename T>
inline bool
operator==(const tree_iterator<T>& x, const tree_const_iterator<T> y)
{ return x.node == y.node; }

template <typename T>
inline bool
operator!=(const tree_iterator<T>& x, const tree_const_iterator<T> y)
{ return x.node != y.node; }

template <typename T>
void
tree_insert_and_rebalance(const bool insert_left,
	tree_node<T>* x, tree_node<T>* p, tree_node<T>& head);

template <typename T>
tree_node<T>*
tree_rebalance_for_erase(tree_node<T>* const z, tree_node<T>& head);

}; // ft::

#include "tree_iterators.ipp"

#endif
