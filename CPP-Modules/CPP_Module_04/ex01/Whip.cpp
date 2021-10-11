#include "Whip.hpp"

Whip::Whip(void) : AWeapon("Whip", 3, 18) {
}

Whip::Whip(Whip const& src) : AWeapon(src._name, src._apcost, src._damage) {
}

Whip::~Whip(void) {
}

Whip&	Whip::operator=(Whip const& src) {
	if (this != &src)
	{
		this->_name = src._name;
		this->_apcost = src._apcost;
		this->_damage = src._damage;
	}
	return *this;
}

void	Whip::attack(void) const {
	std::cout << "* kuh-CHHHH *" << std::endl;
}
