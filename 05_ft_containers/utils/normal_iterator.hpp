#ifndef NORMAL_ITERATOR_HPP
# define NORMAL_ITERATOR_HPP

# include "utils.hpp"

namespace ft {

/*	 ___ _                _             *\
**	|_ _| |_ ___ _ _ __ _| |_ ___ _ _   **
**	 | ||  _/ -_) '_/ _` |  _/ _ \ '_|  **
**	|___|\__\___|_| \__,_|\__\___/_|    **
\*										*/

template<typename Iterator, typename Container>
class normal_iterator
{
	protected:
		Iterator	_current;

		typedef ft::iterator_traits<Iterator>			traits_type;

	public:
		typedef Iterator								iterator_type;
		typedef typename traits_type::iterator_category	iterator_category;
		typedef typename traits_type::value_type		value_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::reference			reference;
		typedef typename traits_type::pointer			pointer;

		normal_iterator()
		: _current(Iterator()) {}

		explicit
		normal_iterator(const Iterator& i)
		: _current(i) {}

		template<typename Iter>
		normal_iterator(const normal_iterator<Iter, Container>& i)
		: _current(i.base()) {}

		// forward iterator requirements
		reference
		operator*() const
		{ return *_current; }

		pointer
		operator->() const
		{ return _current; }

		normal_iterator&
		operator++()
		{ ++_current; return *this; }

		normal_iterator
		operator++(int)
		{ return normal_iterator(_current++); }

		// bidirectional iterator requirements
		normal_iterator&
		operator--()
		{ --_current; return *this; }

		normal_iterator
		operator--(int)
		{ return normal_iterator(_current--); }

		// random access iterator requirements
		reference
		operator[](difference_type n) const
		{ return _current[n]; }

		normal_iterator&
		operator+=(difference_type n)
		{ _current += n; return *this; }

		normal_iterator
		operator+(difference_type n) const
		{ return normal_iterator(_current + n); }

		normal_iterator&
		operator-=(difference_type n)
		{ _current -= n; return *this; }

		normal_iterator
		operator-(difference_type n) const
		{ return normal_iterator(_current - n); }

		const Iterator&
		base() const
		{ return _current; }
};

// forward iterator requirements
template<typename IteratorL, typename IteratorR, typename Container>
inline bool
operator==(const normal_iterator<IteratorL, Container>& lhs,
		   const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() == rhs.base(); }

template<typename Iterator, typename Container>
inline bool
operator==(const normal_iterator<Iterator, Container>& lhs,
		   const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() == rhs.base(); }

template<typename IteratorL, typename IteratorR, typename Container>
inline bool
operator!=(const normal_iterator<IteratorL, Container>& lhs,
		   const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() != rhs.base(); }

template<typename Iterator, typename Container>
inline bool
operator!=(const normal_iterator<Iterator, Container>& lhs,
		   const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() != rhs.base(); }

// random access iterator requirements
template<typename IteratorL, typename IteratorR, typename Container>
inline bool
operator<(const normal_iterator<IteratorL, Container>& lhs,
		  const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() < rhs.base(); }

template<typename Iterator, typename Container>
inline bool
operator<(const normal_iterator<Iterator, Container>& lhs,
		  const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() < rhs.base(); }

template<typename IteratorL, typename IteratorR, typename Container>
inline bool
operator>(const normal_iterator<IteratorL, Container>& lhs,
		  const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() > rhs.base(); }

template<typename Iterator, typename Container>
inline bool
operator>(const normal_iterator<Iterator, Container>& lhs,
		  const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() > rhs.base(); }

template<typename IteratorL, typename IteratorR, typename Container>
inline bool
operator<=(const normal_iterator<IteratorL, Container>& lhs,
		   const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() <= rhs.base(); }

template<typename Iterator, typename Container>
inline bool
operator<=(const normal_iterator<Iterator, Container>& lhs,
		   const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() <= rhs.base(); }

template<typename IteratorL, typename IteratorR, typename Container>
inline bool
operator>=(const normal_iterator<IteratorL, Container>& lhs,
		   const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() >= rhs.base(); }

template<typename Iterator, typename Container>
inline bool
operator>=(const normal_iterator<Iterator, Container>& lhs,
		   const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() >= rhs.base(); }

template<typename IteratorL, typename IteratorR, typename Container>
inline typename normal_iterator<IteratorL, Container>::difference_type
operator-(const normal_iterator<IteratorL, Container>& lhs,
		  const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() - rhs.base(); }

template<typename Iterator, typename Container>
inline typename normal_iterator<Iterator, Container>::difference_type
operator-(const normal_iterator<Iterator, Container>& lhs,
		  const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() - rhs.base(); }

template<typename Iterator, typename Container>
inline normal_iterator<Iterator, Container>
operator+(typename normal_iterator<Iterator, Container>::difference_type n,
		  const normal_iterator<Iterator, Container>& i)
{ return normal_iterator<Iterator, Container>(i.base() + n); }

}; // ft::

#endif
