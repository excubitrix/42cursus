#ifndef ARRAY_H
# define ARRAY_H

template<class T>
class	Array {

	public:

		Array(void);
		Array(unsigned int n);
		Array(Array<T> const& src);
		virtual ~Array(void);

		Array<T>&	operator=(Array<T> const& src);

		T&	operator[](size_t index);
		T const& operator[](size_t index) const;

		class OutOfBoundsException: public std::exception {
			virtual const char* what() const throw();
		};

		size_t	size(void) const;

	private:

		T*		_elem;
		size_t	_size;
};

# include "Array.ipp"

#endif
