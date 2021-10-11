#ifndef MUTANTSTACK_H
# define MUTANTSTACK_H

# include <stack>

template<typename T>
class	MutantStack : public std::stack<T> {

	public:

		MutantStack(void);
		MutantStack(MutantStack<T> const& src);
		virtual ~MutantStack(void);

		MutantStack<T>& operator=(MutantStack<T> const& src);

		typedef typename std::stack<T>::container_type::iterator iterator;
		typedef typename std::stack<T>::container_type::const_iterator const_iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
		typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

		iterator begin(void);
		const_iterator begin(void) const;
		reverse_iterator rbegin(void);
		const_reverse_iterator rbegin(void) const;
		iterator end(void);
		const_iterator end(void) const;
		reverse_iterator rend(void);
		const_reverse_iterator rend(void) const;
};

# include "MutantStack.ipp"

#endif
