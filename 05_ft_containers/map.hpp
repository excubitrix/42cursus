#ifndef MAP_HPP
# define MAP_HPP

# include <memory> // allocator
# include <functional> // less
# include "utils/tree.hpp"
# include "utils/utils.hpp"

namespace ft {

template <class Key,
		  class T,
		  class Compare = std::less<Key>,
		  class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
	public:
		/* ----- MEMBER TYPES ----- */
		typedef	Key														key_type;
		typedef	T														mapped_type;
		typedef	ft::pair<const key_type,mapped_type>					value_type;
		typedef	Compare													key_compare;
		class value_compare
		{
			public:
				Compare comp;
				value_compare(Compare c)
				: comp(c) {}

				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

				bool
				operator()(const value_type& x, const value_type& y) const
				{ return comp(x.first, y.first); }
		};

		typedef	Alloc													allocator_type;
		typedef	typename allocator_type::reference						reference;
		typedef	typename allocator_type::const_reference				const_reference;
		typedef	typename allocator_type::pointer						pointer;
		typedef	typename allocator_type::const_pointer					const_pointer;

	private:
		typedef typename Alloc::template rebind<value_type>::other			pair_alloc_type;
		typedef ft::tree<key_type,value_type,key_compare,pair_alloc_type>	tree_type;

	public:
		typedef typename tree_type::iterator							iterator;
		typedef typename tree_type::const_iterator						const_iterator;

		typedef	typename ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef std::size_t												size_type;

		/* --- MEMBER FUNCTIONS --- */

		/* Constructors, Destructor & Assignment Operator */
		explicit
		map(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		: _tree(comp, alloc) {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
    		const allocator_type& alloc = allocator_type())
		: _tree(comp, alloc)
		{ _tree.insert_unique(first, last); }

		map(const map& x)
		: _tree(x._tree) {}

		~map(void)
		{ clear(); }

		map&
		operator=(const map& x)
		{
			if (this != &x)
				_tree = x._tree;
			return *this;
		}

		/* Iterators */
		iterator
		begin(void)
		{ return _tree.begin(); }
		
		const_iterator
		begin(void) const
		{ return _tree.begin(); }

		iterator
		end(void)
		{ return _tree.end(); }
		
		const_iterator
		end(void) const
		{ return _tree.end(); }

		reverse_iterator
		rbegin(void)
		{ return _tree.rbegin(); }
		
		const_reverse_iterator
		rbegin(void) const
		{ return _tree.rbegin(); }

		reverse_iterator
		rend(void)
		{ return _tree.rend(); }
		
		const_reverse_iterator
		rend(void) const
		{ return _tree.rend(); }

		/* Capacity */
		bool
		empty(void) const
		{ return _tree.empty(); }

		size_type
		size(void) const
		{ return _tree.size(); }

		size_type
		max_size(void) const
		{ return _tree.max_size(); }

		/* Element Access */
		mapped_type&
		operator[](const key_type& k)
		{
			iterator it = lower_bound(k);
			if (it == end() || key_comp()(k, (*it).first))
				it = insert(it, ft::make_pair<const Key, T>(k, mapped_type()));
			return (*it).second;
		}

		/* Modifiers */
		pair<iterator, bool>
		insert(const value_type& val)
		{ return _tree.insert_unique(val); }

		iterator
		insert(iterator position, const value_type& val)
		{ return _tree.insert_unique(position, val); }

		template <class InputIterator>
  		void
		insert(InputIterator first, InputIterator last)
		{ _tree.insert_unique(first, last); }

		void
		erase(iterator position)
		{ _tree.erase(position); }

		size_type
		erase(const key_type& k)
		{ return _tree.erase(k); }

		void
		erase(iterator first, iterator last)
		{ _tree.erase(first, last); }

		void
		swap(map& x)
		{ _tree.swap(x._tree); }

		void
		clear(void)
		{ _tree.clear(); }

		/* Observers */
		key_compare
		key_comp(void) const
		{ return key_compare(); }

		value_compare
		value_comp(void) const
		{ return value_compare(key_compare()); }

		/* Operations */
		iterator
		find(const key_type& k)
		{ return _tree.find(k); }

		const_iterator
		find(const key_type& k) const
		{ return _tree.find(k); }

		size_type
		count(const key_type& k) const
		{ return _tree.find(k) == _tree.end() ? 0 : 1; }

		iterator
		lower_bound(const key_type& k)
		{ return _tree.lower_bound(k); }

		const_iterator
		lower_bound(const key_type& k) const
		{ return _tree.lower_bound(k); }

		iterator
		upper_bound(const key_type& k)
		{ return _tree.upper_bound(k); }

		const_iterator
		upper_bound(const key_type& k) const
		{ return _tree.upper_bound(k); }

		pair<const_iterator,const_iterator>
		equal_range(const key_type& k) const
		{ return _tree.equal_range(k); }

		pair<iterator,iterator>
		equal_range(const key_type& k)
		{ return _tree.equal_range(k); }

		/* Allocator */
		allocator_type
		get_allocator(void) const
		{ return allocator_type(); }

	private:
		template<typename _K1, typename _T1, typename _C1, typename _A1>
		friend bool
		operator==(const map<_K1, _T1, _C1, _A1>&,
				   const map<_K1, _T1, _C1, _A1>&);

		template<typename _K1, typename _T1, typename _C1, typename _A1>
		friend bool
		operator<(const map<_K1, _T1, _C1, _A1>&,
				  const map<_K1, _T1, _C1, _A1>&);

		tree_type _tree;
}; // ft::map

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator==(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
{ return x._tree == y._tree; }

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator<(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
{ return x._tree < y._tree; }

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator!=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
{ return !(x == y); }

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator>(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
{ return y < x; }

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator<=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
{ return !(y < x); }

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator>=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
{ return !(x < y); }

}; // ft::

#endif
