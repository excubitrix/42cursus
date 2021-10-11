#include "Peon.hpp"

Peon::Peon(std::string name) : Victim(name) {
	std::cout << "Zog zog." << std::endl;
}

Peon::Peon(Peon const& src) : Victim(src._name) {
	std::cout << "Copy constructor called" << std::endl;
}

Peon::~Peon(void) {
	std::cout << "Bleuark..." << std::endl;
}

Peon&	Peon::operator=(Peon const& src) {
	std::cout << "Assignation operator called" << std::endl;
	if (this != &src)
		this->_name = src._name;
	return *this;
}

void	Peon::getPolymorphed(void) const {
	std::cout << this->_name + " has been turned into a pink pony!" << std::endl;
}

Peon::Peon(void) : Victim(std::string()) {
	std::cout << "Default constructor called" << std::endl;
}

std::ostream&	operator<<(std::ostream& out, Peon const& src) {
	out << "I'm " + src.getName() + " and I like otters!" << std::endl;
	return out;
}
