#include "Ice.hpp"

Ice::Ice(void) : AMateria("ice") {
}

Ice::Ice(Ice const& src) : AMateria("ice") {
	*this = src;
}

Ice::~Ice(void) {
}

Ice&	Ice::operator=(Ice const& src) {
	if (this != &src)
		this->_xp = src._xp;
	return *this;
}

Ice*	Ice::clone(void) const {
	return new Ice();
}
