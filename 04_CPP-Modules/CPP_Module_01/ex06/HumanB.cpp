#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name) {
	std::cout << "HumanB parameter constructor called" << std::endl;
}

HumanB::~HumanB(void) {
	std::cout << "HumanB destructor called" << std::endl;
}

void	HumanB::setWeapon(Weapon& weapon) {
	this->_weapon = &weapon;
}

void	HumanB::attack(void) const {
	std::cout << this->_name + " attacks with " + this->_weapon->getType() << std::endl;
}
