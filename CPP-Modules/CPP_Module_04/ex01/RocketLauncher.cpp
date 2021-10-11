#include "RocketLauncher.hpp"

RocketLauncher::RocketLauncher(void) : AWeapon("Rocket Launcher", 30, 120) {
}

RocketLauncher::RocketLauncher(RocketLauncher const& src) : AWeapon(src._name, src._apcost, src._damage) {
}

RocketLauncher::~RocketLauncher(void) {
}

RocketLauncher&	RocketLauncher::operator=(RocketLauncher const& src) {
	if (this != &src)
	{
		this->_name = src._name;
		this->_apcost = src._apcost;
		this->_damage = src._damage;
	}
	return *this;
}

void	RocketLauncher::attack(void) const {
	std::cout << "* fwee... SSSSHBLAMM! *" << std::endl;
}
