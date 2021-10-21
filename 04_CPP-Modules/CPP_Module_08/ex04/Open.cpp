#include "Open.hpp"

Open::Open(void) : Token(0, '(') {
}

Open::Open(Open const& src) : Token(0, '(') {
	*this = src;
}

Open::~Open(void) {
}

Open&	Open::operator=(Open const& src) {
	if (this != &src)
		;
	return *this;
}

std::string	Open::getType(void) {
	return "ParOpen";
}

void	Open::execute(Calculator&) {
}
