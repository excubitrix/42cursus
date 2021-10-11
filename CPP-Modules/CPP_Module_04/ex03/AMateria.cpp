#include "AMateria.hpp"

AMateria::AMateria(std::string const& type) : _type(type), _xp(0) {
}

AMateria::AMateria(AMateria const& src) : _xp(src._xp) {
}

AMateria::~AMateria(void) {
}

AMateria&	AMateria::operator=(AMateria const& src) {
	if (this != &src)
		this->_xp = src._xp;
	return *this;
}

std::string const&	AMateria::getType(void) const {
	return this->_type;
}

unsigned int	AMateria::getXP(void) const {
	return this->_xp;
}

void	AMateria::use(ICharacter& target) {
	if (!this->_type.compare("ice"))
		std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
	else if (!this->_type.compare("cure"))
		std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
	this->_xp += 10;
	// std::cout << "XP: " << this->_xp << std::endl;
}

AMateria::AMateria(void) {
}
