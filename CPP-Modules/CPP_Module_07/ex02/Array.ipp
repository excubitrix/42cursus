template<class T>
Array<T>::Array(void) : _elem(new T[0]()), _size(0) {
}

template<class T>
Array<T>::Array(unsigned int n) : _elem(new T[n]()), _size(n) {
}

template<class T>
Array<T>::Array(Array<T> const& src) : _elem(new T[0]()), _size(0) {
	*this = src;
}

template<class T>
Array<T>::~Array(void) {
	delete [] this->_elem;
}

template<class T>
Array<T>&	Array<T>::operator=(Array<T> const& src) {
	if (this != &src)
	{
		delete [] this->_elem;
		this->_size = src.size();
		this->_elem = new T[this->_size]();
		for (size_t i = 0; i < this->_size; i++)
			this->_elem[i] = src._elem[i];
	}
	return *this;
}

template<class T>
T&	Array<T>::operator[](size_t index) {
	if (index >= this->_size)
		throw OutOfBoundsException();
	return this->_elem[index];
}

template<class T>
T const& Array<T>::operator[](size_t index) const {
	return operator[](index);
}

template<class T>
const char* Array<T>::OutOfBoundsException::what() const throw() {
	return "index is out of bounds";
}

template<class T>
size_t	Array<T>::size(void) const {
	return this->_size;
}
