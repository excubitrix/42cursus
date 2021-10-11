#include "Victim.hpp"

Victim::Victim(std::string name) : _name(name) {
	std::cout << "Some random victim called " + this->_name + " just appeared!" << std::endl;
}

Victim::Victim(Victim const& src) : _name(src._name) {
	std::cout << "Copy constructor called" << std::endl;
}

Victim::~Victim(void) {
	std::cout << "Victim " + this->_name + " just died for no apparent reason!" << std::endl;
}

Victim&	Victim::operator=(Victim const& src) {
	std::cout << "Assignation operator called" << std::endl;
	if (this != &src)
		this->_name = src._name;
	return *this;
}

std::string	Victim::getName(void) const {
	return this->_name;
}

void	Victim::getPolymorphed(void) const {
	std::cout << this->_name + " has been turned into a cute little sheep!" << std::endl;
}

Victim::Victim(void) {
	std::cout << "Default constructor called" << std::endl;
}

std::ostream&	operator<<(std::ostream& out, Victim const& src) {
	out << "I'm " + src.getName() + " and I like otters!" << std::endl;
	return out;
}
