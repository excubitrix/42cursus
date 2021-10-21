#include "Span.hpp"

Span::Span(size_t N) : _N(N) {
}

Span::Span(Span const& src) {
	*this = src;
}

Span::~Span(void) {
	this->_numbers.clear();
}

Span& Span::operator=(Span const& src) {
	if (this != &src)
	{
		this->_N = src._N;
		this->_numbers.clear();
		this->_numbers = src._numbers;
	}
	return *this;
}

const char* Span::OutOfSpaceException::what() const throw() {
	return "Out of space";
}

const char* Span::NotEnoughNumbersException::what() const throw() {
	return "Not enough numbers";
}

void	Span::addNumber(int value) {
	if (this->_numbers.size() == this->_N)
		throw OutOfSpaceException();
	this->_numbers.insert(value);
}

size_t	Span::shortestSpan(void) const {
	if (this->_numbers.size() < 2)
		throw NotEnoughNumbersException();
	int* result = new int[this->_numbers.size()];
	std::adjacent_difference(this->_numbers.begin(), this->_numbers.end(), result);
	int min = *std::min_element(result + 1, result + this->_numbers.size());
	delete [] result;
	return min;
}

size_t	Span::longestSpan(void) const {
	return *std::max_element(this->_numbers.begin(), this->_numbers.end()) -
			*std::min_element(this->_numbers.begin(), this->_numbers.end());
}

void	print(const int& n) {
	std::cout << n << " ";
}

void	Span::printNumbers(void) const {
	std::for_each(this->_numbers.begin(), this->_numbers.end(), print);
	std::cout << std::endl;
}

Span::Span() : _N(0) {
}
