#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include "utils/utils.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T 			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

			explicit
			stack(const container_type& ctnr = container_type())
			{ c = ctnr; }
			
			bool
			empty() const
			{ return(c.empty()); }
			
			size_type
			size() const
			{ return (c.size()); }
			
			value_type&
			top()
			{ return (c.back()); }

			const value_type&
			top() const
			{ return (c.back()); }
			
			void
			push(const value_type& val)
			{ c.push_back(val); }

			void
			pop()
			{ c.pop_back(); }
		
		protected:
			container_type c;

		private:
			template<typename _T1, typename _S1>
			friend bool
			operator==(const stack<_T1, _S1>&, const stack<_T1, _S1>&);

			template<typename _T1, typename _S1>
			friend bool
			operator<(const stack<_T1, _S1>&, const stack<_T1, _S1>&);
	}; // ft::stack

	// NON MEMBER FUNCTION OVERLOADS
	// relational operators
	template <class T, class Container>
	bool
	operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs.c == rhs.c; }
	
	template <class T, class Container>
	bool
	operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(lhs == rhs); }
	
	template <class T, class Container>
	bool
	operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs.c < rhs.c; }
	
	template <class T, class Container>
	bool
	operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(rhs < lhs); }
	
	template <class T, class Container>
	bool
	operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return rhs < lhs; }
	
	template <class T, class Container>
	bool
	operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(lhs < rhs); }
} // ft::

#endif
