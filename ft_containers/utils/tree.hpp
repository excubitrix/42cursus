#ifndef TREE_HPP
# define TREE_HPP

# include "tree_iterators.hpp"
# include "utils.hpp"

namespace ft {

/*   ___ _                      ___                  _      _____              *\
**	| _ |_)_ _  __ _ _ _ _  _  / __| ___ __ _ _ _ __| |_   |_   _| _ ___ ___   **
**	| _ \ | ' \/ _` | '_| || | \__ \/ -_) _` | '_/ _| ' \    | || '_/ -_) -_)  **
**	|___/_|_||_\__,_|_|  \_, | |___/\___\__,_|_| \__|_||_|   |_||_| \___\___|  **
\*						 |__/												   */

template <typename Key, typename Val, typename Compare,
		  typename Alloc = std::allocator<Val> >
class tree
{
	typedef typename Alloc::template rebind<tree_node<Val> >::other	node_allocator;

	protected:
		typedef tree_node<Val>					Node;
		typedef Node*							node_ptr;
		typedef const Node*						const_node_ptr;

	public:
		typedef Key								key_type;
		typedef Val								value_type;

		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;

		typedef std::size_t						size_type;
		typedef std::ptrdiff_t					difference_type;
		typedef Alloc							allocator_type;

		node_allocator&
		get_node_allocator()
		{ return *static_cast<node_allocator*>(&this->_attr); }

		const node_allocator&
		get_node_allocator() const
		{ return *static_cast<const node_allocator*>(&this->_attr); }

		allocator_type
		get_allocator() const
		{ return allocator_type(get_node_allocator()); }

	protected:
		node_ptr
		get_node()
		{ return _attr.node_allocator::allocate(1); }

		void
		put_node(node_ptr p)
		{ _attr.node_allocator::deallocate(p, 1); }

		node_ptr
		create_node(const value_type& x)
		{
			node_ptr tmp = get_node();
			try
			{
				get_allocator().construct(&tmp->value, x);
			}
			catch(...)
			{
				put_node(tmp);
				throw ;
			}
			return tmp;
		}

		void
		destroy_node(node_ptr p)
		{
			get_node_allocator().destroy(p);
			put_node(p);
		}

		node_ptr
		clone_node(const_node_ptr x)
		{
			node_ptr tmp = create_node(x->value);
			tmp->color = x->color;
			tmp->left = 0;
			tmp->right = 0;
			return tmp;
		}

	protected:
		template<typename Key_compare>
		struct tree_attr : public node_allocator
		{
				Key_compare		key_comp;
				Node			head;
				size_type		node_count;

				tree_attr()
				: node_allocator(), key_comp(), head(), node_count(0)
				{ _initialize(); }

				tree_attr(const Key_compare& comp, const node_allocator& a)
				: node_allocator(a), key_comp(comp), head(), node_count(0)
				{ _initialize(); }

			private:
				void
				_initialize()
				{
					this->head.color = red;
					this->head.parent = 0;
					this->head.left = &this->head;
					this->head.right = &this->head;
				}
		};

		tree_attr<Compare> _attr;

	public:
		node_ptr&
		_root()
		{ return this->_attr.head.parent; }

		const_node_ptr
		_root() const
		{ return this->_attr.head.parent; }

		node_ptr&
		_leftmost()
		{ return this->_attr.head.left; }

		const_node_ptr
		_leftmost() const
		{ return this->_attr.head.left; }

		node_ptr&
		_rightmost()
		{ return this->_attr.head.right; }

		const_node_ptr
		_rightmost() const
		{ return this->_attr.head.right; }

		node_ptr
		_begin()
		{ return this->_attr.head.parent; }

		const_node_ptr
		_begin() const
		{ return this->_attr.head.parent; }

		node_ptr
		_end()
		{ return &this->_attr.head; }

		const_node_ptr
		_end() const
		{ return &this->_attr.head; }

		static const key_type&
		_key(const_node_ptr p)
		{ return p->value.first; }

		static const key_type&
		_key(const value_type& v)
		{ return v.first; }

		static node_ptr
		minimum(node_ptr x)
		{ return tree_node<Val>::minimum(x); }

		static const_node_ptr
		minimum(const_node_ptr x)
		{ return tree_node<Val>::minimum(x); }

		static node_ptr
		maximum(node_ptr x)
		{ return tree_node<Val>::maximum(x); }

		static const_node_ptr
		maximum(const_node_ptr x)
		{ return tree_node<Val>::maximum(x); }

	public:
		typedef ft::tree_iterator<value_type>			iterator;
		typedef ft::tree_const_iterator<value_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		void
		clear()
		{
			erase(_begin());
			_leftmost() = _end();
			_root() = 0;
			_rightmost() = _end();
			this->_attr.node_count = 0;
		}

	private:
		iterator
		insert(const_node_ptr x, const_node_ptr p, const value_type& v)
		{
			bool insert_left = (x != 0 || p == _end() || _attr.key_comp(_key(v), _key(p)));

			node_ptr z = create_node(v);

			ft::tree_insert_and_rebalance(insert_left, z, const_cast<node_ptr>(p), this->_attr.head);
			++_attr.node_count;
			return iterator(z);
		}

		void
		erase(node_ptr x)
		{
			while (x != 0)
			{
				erase(x->right);
				node_ptr y = x->left;
				destroy_node(x);
				x = y;
			}
		}

		node_ptr
		copy(const_node_ptr x, node_ptr p)
		{
			// x and p must be non-null
			node_ptr top = clone_node(x);
			top->parent = p;

			try
			{
				if (x->right)
					top->right = copy(x->right, top);
				p = top;
				x = x->left;

				while (x != 0)
				{
					node_ptr y = clone_node(x);
					p->left = y;
					y->parent = p;
					if (x->right)
						y->right = copy(x->right, y);
					p = y;
					x = x->left;
				}
			}
			catch(...)
			{
				erase(top);
				throw ;
			}
			return top;
		}

	public:
		tree()
		{}

		tree(const Compare& comp, const allocator_type& a = allocator_type())
		: _attr(comp, a) {}

		tree(const tree& x)
		: _attr(x._attr.key_comp, x.get_node_allocator())
		{
			if (x._root() != 0)
			{
				_root() = copy(x._begin(), _end());
				_leftmost() = minimum(_root());
				_rightmost() = maximum(_root());
				_attr.node_count = x._attr.node_count;
			}
		}

		~tree()
		{ erase(_begin()); }

		tree&
		operator=(const tree<Key, Val, Compare, Alloc>& x)
		{
			if (this != &x)
			{
				clear();
				_attr.key_comp = x._attr.key_comp;
				if (x._root() != 0)
				{
					_root() = copy(x._begin(), _end());
					_leftmost() = minimum(_root());
					_rightmost() = maximum(_root());
					_attr.node_count = x._attr.node_count;
				}
			}
			return *this;
		}

	public:
		iterator
		begin()
		{ return iterator(this->_attr.head.left); }

		const_iterator
		begin() const
		{ return const_iterator(static_cast<const_node_ptr>(this->_attr.head.left)); }

		iterator
		end()
		{ return iterator(&this->_attr.head); }

		const_iterator
		end() const
		{ return const_iterator(static_cast<const_node_ptr>(&this->_attr.head)); }

		reverse_iterator
		rbegin()
		{ return reverse_iterator(end()); }

		const_reverse_iterator
		rbegin() const
		{ return const_reverse_iterator(end()); }

		reverse_iterator
		rend()
		{ return reverse_iterator(begin()); }

		const_reverse_iterator
		rend() const
		{ return const_reverse_iterator(begin()); }

		bool
		empty() const
		{ return this->_attr.node_count == 0; }

		size_type
		size() const
		{ return this->_attr.node_count; }

		size_type
		max_size() const
		{ return get_node_allocator().max_size(); }

		iterator
		lower_bound(const key_type& k)
		{ return lower_bound(_begin(), _end(), k); }

		const_iterator
		lower_bound(const key_type& k) const
		{ return lower_bound(_begin(), _end(), k); }

		iterator
		upper_bound(const key_type& k)
		{ return upper_bound(_begin(), _end(), k); }

		const_iterator
		upper_bound(const key_type& k) const
		{ return upper_bound(_begin(), _end(), k); }

		iterator
		lower_bound(node_ptr x, node_ptr y, const key_type& k)
		{
			while (x != 0)
			{
				if (!_attr.key_comp(_key(x), k))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return iterator(y);
		}

		const_iterator
		lower_bound(const_node_ptr x, const_node_ptr y, const key_type& k) const
		{
			while (x != 0)
			{
				if (!_attr.key_comp(_key(x), k))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return const_iterator(y);
		}

		iterator
		upper_bound(node_ptr x, node_ptr y, const key_type& k)
		{
			while (x != 0)
			{
				if (_attr.key_comp(k, _key(x)))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return iterator(y);
		}

		const_iterator
		upper_bound(const_node_ptr x, const_node_ptr y, const key_type& k) const
		{
			while (x != 0)
			{
				if (_attr.key_comp(k, _key(x)))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return const_iterator(y);
		}

		ft::pair<iterator,iterator>
		equal_range(const key_type& k)
		{
			node_ptr x = _begin();
			node_ptr y = _end();
			while (x != 0)
			{
				if (_attr.key_comp(_key(x), k))
					x = x->right;
				else if (_attr.key_comp(k, _key(x)))
				{
					y = x;
					x = x->left;
				}
				else
				{
					node_ptr xu(x);
					node_ptr yu(y);
					y = x;
					x = x->left;
					xu = xu->right;
					return ft::make_pair<iterator,iterator>(lower_bound(x, y, k),
						upper_bound(xu, yu, k));
				}
			}
			return ft::make_pair<iterator,iterator>(iterator(y), iterator(y));
		}

		ft::pair<const_iterator,const_iterator>
		equal_range(const key_type& k) const
		{
			const_node_ptr x = _begin();
			const_node_ptr y = _end();
			while (x != 0)
			{
				if (_attr.key_comp(_key(x), k))
					x = x->right;
				else if (_attr.key_comp(k, _key(x)))
				{
					y = x;
					x = x->left;
				}
				else
				{
					const_node_ptr xu(x);
					const_node_ptr yu(y);
					y = x;
					x = x->left;
					xu = xu->right;
					return ft::make_pair<const_iterator,const_iterator>(
						lower_bound(x, y, k), upper_bound(xu, yu, k));
				}
			}
			return ft::make_pair<const_iterator,const_iterator>(const_iterator(y),
				const_iterator(y));
		}

		size_type
		erase(const key_type& x)
		{
			ft::pair<iterator,iterator> p = equal_range(x);
			const size_type old_size = size();
			erase(p.first, p.second);
			return old_size - size();
		}

		iterator
		find(const key_type& k)
		{
			iterator j = lower_bound(_begin(), _end(), k);
			if (j == end() || _attr.key_comp(k, _key(j.current())))
				return end();
			return j;
		}

		const_iterator
		find(const key_type& k) const
		{
			const_iterator j = lower_bound(_begin(), _end(), k);
			if (j == end() || _attr.key_comp(k, _key(j.current())))
				return end();
			return j;
		}

		void
		swap(tree& t)
		{
			if (_root() == 0)
			{
				if (t._root() != 0)
				{
					_root() = t._root();
					_leftmost() = t._leftmost();
					_rightmost() = t._rightmost();
					_root()->parent = _end();

					t._root() = 0;
					t._leftmost() = t._end();
					t._rightmost() = t._end();
				}
			}
			else if (t._root() == 0)
			{
				t._root() = _root();
				t._leftmost() = _leftmost();
				t._rightmost() = _rightmost();
				t._root()->parent = t._end();

				_root() = 0;
				_leftmost() = _end();
				_rightmost() = _end();
			}
			else
			{
				std::swap(_root(), t._root());
				std::swap(_leftmost(), t._leftmost());
				std::swap(_rightmost(), t._rightmost());

				_root()->parent = _end();
				t._root()->parent = t._end();
			}
			std::swap(this->_attr.node_count, t._attr.node_count);
		}

		ft::pair<iterator, bool>
		insert_unique(const value_type& v)
		{
			node_ptr x = _begin();
			node_ptr y = _end();
			bool side = true;
			while (x != 0)
			{
				y = x;
				side = _attr.key_comp(_key(v), _key(x));
				x = side ? x->left : x->right;
			}
			iterator j = iterator(y);
			if (side)
			{
				if (j == begin())
					return ft::make_pair<iterator, bool>(insert(x, y, v), true);
				else
					--j;
			}
			if (_attr.key_comp(_key(j.current()), _key(v)))
				return ft::make_pair<iterator, bool>(insert(x, y, v), true);
			return ft::make_pair<iterator, bool>(j, false);
		}

		iterator
		insert_unique(const_iterator position, const value_type& v)
		{
			if (position.current() == _end()) // end
			{
				if (size() > 0 && _attr.key_comp(_key(_rightmost()), _key(v)))
					return insert(0, _rightmost(), v);
				else
					return insert_unique(v).first;
			}
			else if (_attr.key_comp(_key(v), _key(position.current())))
			{
				const_iterator before = position;
				if (position.current() == _leftmost()) // begin
					return insert(_leftmost(), _leftmost(), v);
				else if (_attr.key_comp(_key((--before).current()), _key(v)))
				{
					if (before.current()->right == 0)
						return insert(0, before.current(), v);
					else
						return insert(position.current(), position.current(), v);
				}
				else
					return insert_unique(v).first;
			}
			else if (_attr.key_comp(_key(position.current()), _key(v)))
			{
				const_iterator after = position;
				if (position.current() == _rightmost())
					return insert(0, _rightmost(), v);
				else if (_attr.key_comp(_key(v), _key((++after).current())))
				{
					if (position.current()->right == 0)
						return insert(0, position.current(), v);
					else
						return insert(after.current(), after.current(), v);
				}
				else
					return insert_unique(v).first;
			}
			else // equivalent keys
				return position._const_cast();
		}

		template <typename InputIterator>
		void
		insert_unique(InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				insert_unique(end(), *first);
		}

		void
		erase(const_iterator position)
		{
			node_ptr y = static_cast<node_ptr>(tree_rebalance_for_erase(
				const_cast<node_ptr>(position.current()), this->_attr.head));
			destroy_node(y);
			--_attr.node_count;
		}

		void
		erase(const_iterator first, const_iterator last)
		{
			if (first == begin() && last == end())
				clear();
			else
			{
				while (first != last)
					erase(first++);
			}
		}
};

template<typename Key, typename Val, typename Compare, typename Alloc>
inline bool
operator==(const tree<Key,Val,Compare,Alloc>& x, const tree<Key,Val,Compare,Alloc>& y)
{ return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()); }

template<typename Key, typename Val, typename Compare, typename Alloc>
inline bool
operator<(const tree<Key,Val,Compare,Alloc>& x, const tree<Key,Val,Compare,Alloc>& y)
{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

}; // ft::

#endif
