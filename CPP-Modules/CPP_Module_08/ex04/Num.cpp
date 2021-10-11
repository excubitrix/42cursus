#include "Num.hpp"

Num::Num(int value) : Token(value, 0) {
}

Num::Num(Num const& src) : Token(src._value, 0) {
}

Num::~Num(void) {
}

Num&	Num::operator=(Num const& src) {
	if (this != &src)
		this->_value = src._value;
	return *this;
}

std::string	Num::getType(void) {
	std::stringstream ss;
	ss << "Num(" << this->_value << ")";
	return ss.str();
}

void	Num::execute(Calculator& c) {
	std::cout << "Push\t";
	c.push(this->_value);
}
