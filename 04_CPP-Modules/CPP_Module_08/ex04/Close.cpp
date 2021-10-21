#include "Close.hpp"

Close::Close(void) : Token(0, ')') {
}

Close::Close(Close const& src) : Token(0, ')') {
	*this = src;
}

Close::~Close(void) {
}

Close&	Close::operator=(Close const& src) {
	if (this != &src)
		;
	return *this;
}

std::string	Close::getType(void) {
	return "ParClose";
}

void	Close::execute(Calculator&) {
}
