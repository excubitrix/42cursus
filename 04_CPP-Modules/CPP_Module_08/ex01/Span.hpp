#ifndef SPAN_H
# define SPAN_H

# include <algorithm>
# include <iostream>
# include <numeric>
# include <set>

class	Span {

	public:
		Span(size_t N);
		Span(Span const& src);
		virtual ~Span(void);

		Span& operator=(Span const& src);

		class OutOfSpaceException: public std::exception {
			virtual const char* what() const throw();
		};

		class NotEnoughNumbersException: public std::exception {
			virtual const char* what() const throw();
		};

		void	addNumber(int value);
		template<typename Iterator>
		void	addNumber(Iterator begin, Iterator end);

		size_t	shortestSpan(void) const;
		size_t	longestSpan(void) const;

		void	printNumbers(void) const;

	private:

		size_t				_N;
		std::multiset<int>	_numbers;

		Span(void);
};

void	print(const int& n);

# include "Span.ipp"

#endif
