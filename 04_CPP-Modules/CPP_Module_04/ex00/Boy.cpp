#include "Boy.hpp"

Boy::Boy(std::string name) : Victim(name) {
	std::cout << "I can move! I can talk! I can walk!" << std::endl;
}

Boy::Boy(Boy const& src) : Victim(src._name) {
	std::cout << "Copy constructor called" << std::endl;
}

Boy::~Boy(void) {
	std::cout << "Hee-haw." << std::endl;
}

Boy&	Boy::operator=(Boy const& src) {
	std::cout << "Assignation operator called" << std::endl;
	if (this != &src)
		this->_name = src._name;
	return *this;
}

void	Boy::getPolymorphed(void) const {
	std::cout << this->_name + " has been turned into a donkey!" << std::endl;
}

Boy::Boy(void) : Victim(std::string()) {
	std::cout << "Default constructor called" << std::endl;
}

std::ostream&	operator<<(std::ostream& out, Boy const& src) {
	out << "I'm " + src.getName() + " and I like crickets!" << std::endl;
	return out;
}
