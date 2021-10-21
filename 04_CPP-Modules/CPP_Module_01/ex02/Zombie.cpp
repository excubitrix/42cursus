#include "Zombie.hpp"

std::string	const	Zombie::_growl[4] = {
	"BLEEEEAGGHAAAAH!",
	"GRHAAAAHAHRHAHHAAAA!",
	"Uhhhhggghhh.",
	"RAAAWWWHHAA!"
};

Zombie::Zombie(std::string name, std::string type) : _name(name), _type(type) {
	std::cout << "Zombie parameter constructor called: A " + this->_type
			  << " zombie named " + this->_name + " appears." << std::endl;
}

Zombie::~Zombie(void) {
	std::cout << "Zombie destructor called: The " + this->_type + " zombie named "
			  << this->_name + " has been defeated." << std::endl;
}

void	Zombie::announce(void) const {
	std::cout << "<" + this->_name + " (" + this->_type + ")> " + _get_growl() << std::endl;
}

std::string	const	Zombie::_get_growl(void) const {
	return this->_growl[rand() % 4];
}
