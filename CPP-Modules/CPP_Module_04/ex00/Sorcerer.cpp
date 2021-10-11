#include "Sorcerer.hpp"

Sorcerer::Sorcerer(std::string name, std::string title) : _name(name), _title(title) {
	std::cout << this->_name + ", " + this->_title + ", is born!" << std::endl;
}

Sorcerer::Sorcerer(Sorcerer const& src) : _name(src._name), _title(src._title) {
	std::cout << "Copy constructor called" << std::endl;
}

Sorcerer::~Sorcerer(void) {
	std::cout << this->_name + ", " + this->_title + ", is dead. Consequences will never be the same!" << std::endl;
}

Sorcerer&	Sorcerer::operator=(Sorcerer const& src) {
	std::cout << "Assignation operator called" << std::endl;
	if (this != &src)
	{
		this->_name = src._name;
		this->_title = src._title;
	}
	return *this;
}

std::string	Sorcerer::getName(void) const {
	return this->_name;
}

std::string	Sorcerer::getTitle(void) const {
	return this->_title;
}

void	Sorcerer::polymorph(Victim const& victim) const {
	victim.getPolymorphed();
}

Sorcerer::Sorcerer(void) {
	std::cout << "Default constructor called" << std::endl;
}

std::ostream&	operator<<(std::ostream& out, Sorcerer const& src) {
	out << "I am " + src.getName() + ", " + src.getTitle() + ", and I like ponies!" << std::endl;
	return out;
}
