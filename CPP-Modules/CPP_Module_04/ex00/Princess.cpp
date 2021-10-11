#include "Princess.hpp"

Princess::Princess(std::string name) : Victim(name) {
	std::cout << "* giggles *" << std::endl;
}

Princess::Princess(Princess const& src) : Victim(src._name) {
	std::cout << "Copy constructor called" << std::endl;
}

Princess::~Princess(void) {
	std::cout << "I'm too pretty to die!" << std::endl;
}

Princess&	Princess::operator=(Princess const& src) {
	std::cout << "Assignation operator called" << std::endl;
	if (this != &src)
		this->_name = src._name;
	return *this;
}

void	Princess::getPolymorphed(void) const {
	std::cout << this->_name + " has been turned into a frog!" << std::endl;
}

Princess::Princess(void) : Victim(std::string()) {
	std::cout << "Default constructor called" << std::endl;
}

std::ostream&	operator<<(std::ostream& out, Princess const& src) {
	out << "I'm " + src.getName() + " and I like tiaras!" << std::endl;
	return out;
}
