template<typename Iterator>
void	Span::addNumber(Iterator begin, Iterator end)
{
	if (this->_numbers.size() + std::distance(begin, end) > this->_N)
		throw Span::OutOfSpaceException();
	this->_numbers.insert(begin, end);
}
