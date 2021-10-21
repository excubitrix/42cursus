#ifndef UTILS_HPP
# define UTILS_HPP

#include <cstddef>  // ptrdiff_t
#include <iostream>

namespace ft {

/*	 ___      _       *\
**	| _ \__ _(_)_ _   **
**	|  _/ _` | | '_|  **
**	|_| \__,_|_|_| 	  **
\*					  */

template <class T1, class T2>
struct pair {
	typedef T1	first_type;
	typedef T2	second_type;

	first_type	first;
	second_type	second;

	pair(void)
	: first(), second() {}

	template <class U, class V>
	pair(const pair<U, V>& pr)
	: first(pr.first), second(pr.second) {}

	pair(const first_type& a, const second_type& b)
	: first(a), second(b) {}

	pair&
	operator=(const pair& pr)
	{
		if (this != &pr)
		{
			this->first = pr.first;
			this->second = pr.second;
		}
		return *this;
	}
};

template <class T1, class T2>
bool
operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{ return lhs.first == rhs.first && lhs.second == rhs.second; }

template <class T1, class T2>
bool
operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{ return !(lhs == rhs); }

template <class T1, class T2>
bool
operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

template <class T1, class T2>
bool
operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{ return !(rhs < lhs); }

template <class T1, class T2>
bool
operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{ return rhs < lhs; }

template <class T1, class T2>
bool
operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{ return !(lhs < rhs); }

/*	 __  __      _         ___      _     	*\
**	|  \/  |__ _| |_____  | _ \__ _(_)_ _ 	**
**	| |\/| / _` | / / -_) |  _/ _` | | '_|	**
**	|_|  |_\__,_|_\_\___| |_| \__,_|_|_| 	**
\*											*/

template <class T1, class T2>
pair<T1, T2>
make_pair(const T1& x, const T2& y)
{ return pair<T1, T2>(x, y); }

/*	 ___ _                _           	*\
**	|_ _| |_ ___ _ _ __ _| |_ ___ _ _ 	**
**	 | ||  _/ -_) '_/ _` |  _/ _ \ '_|	**
**	|___|\__\___|_| \__,_|\__\___/_|  	**
\*										*/

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename Category, typename T, typename Distance = std::ptrdiff_t,
		  typename Pointer = T*, typename Reference = T& >
struct iterator
{
	typedef Category    iterator_category;
	typedef T           value_type;
	typedef Distance    difference_type;
	typedef Pointer     pointer;
	typedef Reference   reference;
};

/*	  ___ _                _             _____         _ _      	*\
**	 |_ _| |_ ___ _ _ __ _| |_ ___ _ _  |_   _| _ __ _(_) |_ ___	**
**	  | ||  _/ -_) '_/ _` |  _/ _ \ '_|   | || '_/ _` | |  _(_-<	**
**	 |___|\__\___|_| \__,_|\__\___/_|     |_||_| \__,_|_|\__/__/	**
\*																	*/

template <class Iterator>
class iterator_traits {
	public:
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
};

template <class T>
class iterator_traits<T*> {
	public:
		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::random_access_iterator_tag		iterator_category;
};

template <class T>
class iterator_traits<const T*> {
	public:
		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef const T*							pointer;
		typedef const T&							reference;
		typedef std::random_access_iterator_tag		iterator_category;
};

/*	 ___                          ___ _                _           	 *\
**	| _ \_____ _____ _ _ ______  |_ _| |_ ___ _ _ __ _| |_ ___ _ _ 	 **
**	|   / -_) V / -_) '_(_-< -_)  | ||  _/ -_) '_/ _` |  _/ _ \ '_|	 **
**	|_|_\___|\_/\___|_| /__|___| |___|\__\___|_| \__,_|\__\___/_|  	 **
\*																	 */

template <class Iterator>
class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
										 typename iterator_traits<Iterator>::value_type,
										 typename iterator_traits<Iterator>::difference_type,
										 typename iterator_traits<Iterator>::pointer,
										 typename iterator_traits<Iterator>::reference>
{
	protected:
		Iterator	current;

		typedef iterator_traits<Iterator>	traits_type;

	public:
		typedef Iterator								iterator_type;
		typedef typename traits_type::iterator_category	iterator_category;
		typedef typename traits_type::value_type		value_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::pointer			pointer;
		typedef typename traits_type::reference			reference;

		reverse_iterator()
		: current() {}

		explicit reverse_iterator(iterator_type it)
		: current(it) {}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it)
		: current(rev_it.base()) {}

		iterator_type
		base() const
		{ return current; }

		reference
		operator*() const
		{ iterator_type tmp = current; return *--tmp; }

		reverse_iterator
		operator+(difference_type n) const
		{ return reverse_iterator(current - n); }

		reverse_iterator&
		operator++()
		{ --current; return *this; }

		reverse_iterator
		operator++(int)
		{
			reverse_iterator tmp = *this;
			--current;
			return tmp;
		}

		reverse_iterator&
		operator+=(difference_type n)
		{ current -= n; return *this; }

		reverse_iterator
		operator-(difference_type n) const
		{ return reverse_iterator(current + n); }

		reverse_iterator&
		operator--()
		{ ++current; return *this; }

		reverse_iterator
		operator--(int)
		{
			reverse_iterator tmp = *this;
			++current;
			return tmp;
		}

		reverse_iterator&
		operator-=(difference_type n)
		{ current += n; return *this; }

		pointer
		operator->() const
		{ return &(operator*()); }

		reference
		operator[](difference_type n) const
		{ return *(*this + n); }
};

template <class Iterator>
bool
operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{ return lhs.base() == rhs.base(); }
				
template <class Iterator>
bool
operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{ return !(lhs == rhs); }
				
template <class Iterator>
bool
operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{ return rhs.base() < lhs.base(); }
			   
template <class Iterator>
bool
operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{ return !(rhs < lhs); }
				
template <class Iterator>
bool
operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{ return rhs < lhs; }
			   
template <class Iterator>
bool
operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{ return !(lhs < rhs); }

template <class Iterator>
reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n,
		  const reverse_iterator<Iterator>& rev_it)
{ return reverse_iterator<Iterator>(rev_it.base() - n); }

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{ return rhs.base() - lhs.base(); }

// comparison of reverse_iterator to const reverse_iterator
template <class IteratorL, class IteratorR>
bool
operator==(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
{ return lhs.base() == rhs.base(); }
				
template <class IteratorL, class IteratorR>
bool
operator!=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
{ return !(lhs == rhs); }
				
template <class IteratorL, class IteratorR>
bool
operator<(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
{ return rhs.base() < lhs.base(); }
			   
template <class IteratorL, class IteratorR>
bool
operator<=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
{ return !(rhs < lhs); }
				
template <class IteratorL, class IteratorR>
bool
operator>(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
{ return rhs < lhs; }
			   
template <class IteratorL, class IteratorR>
bool
operator>=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
{ return !(lhs < rhs); }

template <class IteratorL, class IteratorR>
typename reverse_iterator<IteratorL>::difference_type
operator-( const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
{ return rhs.base() - lhs.base(); }

/*	                _    _           _  __ 	*\
**	  ___ _ _  __ _| |__| |___      (_)/ _|	**
**	 / -_) ' \/ _` | '_ \ / -_)     | |  _|	**
**	 \___|_||_\__,_|_.__/_\___| ___ |_|_|  	**
\*	                           |___|       	*/

template <bool Cond, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T>
{ typedef T type; };

/*	  _          _     _                     _ 	*\
**	 (_)___     (_)_ _| |_ ___ __ _ _ _ __ _| |	**
**	 | (_-<     | | ' \  _/ -_) _` | '_/ _` | |	**
**	 |_/__/ ___ |_|_||_\__\___\__, |_| \__,_|_|	**
\*	       |___|              |___/            	*/

// implementation adapted from https://www.cplusplus.com/reference/type_traits/integral_constant/?kw=integral_constant
template <class T, T v>
struct integral_constant
{
	static const T value = v;
	typedef T value_type;
	typedef integral_constant<T,v> type;
	operator T() { return v; }
};

template <class _Tp> struct is_integral                     : public ft::integral_constant<bool, false> {};
template <>          struct is_integral<bool>               : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<char>               : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<signed char>        : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<unsigned char>      : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<wchar_t>            : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<short>              : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<unsigned short>     : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<int>                : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<unsigned int>       : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<long>               : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<unsigned long>      : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<long long>          : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<unsigned long long> : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<__int128_t>         : public ft::integral_constant<bool, true> {};
template <>          struct is_integral<__uint128_t>        : public ft::integral_constant<bool, true> {};

/*	                      _ 	*\
**	   ___ __ _ _  _ __ _| |	**
**	  / -_) _` | || / _` | |	**
**	  \___\__, |\_,_\__,_|_|	**
\*	         |_|            	*/

// 1. equality
template <class InputIterator1, class InputIterator2>
bool
equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1!=last1)
	{
		if (!(*first1 == *first2))
			return false;
		++first1; ++first2;
	}
	return true;
}

// 2. predicate
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool
equal(InputIterator1 first1, InputIterator1 last1,
	  InputIterator2 first2, BinaryPredicate pred)
{
	while (first1!=last1)
	{
		if (!pred(*first1,*first2))
			return false;
		++first1; ++first2;
	}
	return true;
}

/*	 _         _                            _    _         _                                         *\
**	| |_____ _(_)__ ___  __ _ _ _ __ _ _ __| |_ (_)__ __ _| |      __ ___ _ __  _ __  __ _ _ _ ___   **
**	| / -_) \ / / _/ _ \/ _` | '_/ _` | '_ \ ' \| / _/ _` | |     / _/ _ \ '  \| '_ \/ _` | '_/ -_)  **
**	|_\___/_\_\_\__\___/\__, |_| \__,_| .__/_||_|_\__\__,_|_| ___ \__\___/_|_|_| .__/\__,_|_| \___|  **
\*	                    |___/         |_|                    |___|             |_|                   */

// 1. default
template <class InputIterator1, class InputIterator2>
bool
lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
		++first1;
		++first2;
	}
	return (first2 != last2);
}

// 2. custom
template <class InputIterator1, class InputIterator2, class Compare>
bool
lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2, Compare comp)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (comp(*first1, *first2))
			return true;
		++first1;
		++first2;
	}
	return (first2 != last2);
}

}; // ft::

#endif
