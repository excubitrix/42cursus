#include "Cure.hpp"

Cure::Cure(void) : AMateria("cure") {
}

Cure::Cure(Cure const& src) : AMateria("cure") {
	*this = src;
}

Cure::~Cure(void) {
}

Cure&	Cure::operator=(Cure const& src) {
	if (this != &src)
		this->_xp = src._xp;
	return *this;
}

Cure*	Cure::clone(void) const {
	return new Cure();
}
