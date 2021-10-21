#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon& weapon) : _name(name), _weapon(weapon) {
	std::cout << "HumanA parameter constructor called" << std::endl;
}

HumanA::~HumanA(void) {
	std::cout << "HumanA destructor called" << std::endl;
}

void	HumanA::attack(void) const {
	std::cout << this->_name + " attacks with " + this->_weapon.getType() << std::endl;
}
