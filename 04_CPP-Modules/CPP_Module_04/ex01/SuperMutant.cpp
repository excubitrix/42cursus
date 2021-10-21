#include "SuperMutant.hpp"

SuperMutant::SuperMutant(void) : Enemy(170, "Super Mutant") {
	std::cout << "Gaaah. Me want smash heads!" << std::endl;
}

SuperMutant::SuperMutant(SuperMutant const& src) : Enemy(src._hp, src._type) {
}

SuperMutant::~SuperMutant(void) {
	std::cout << "Aaargh..." << std::endl;
}

SuperMutant&	SuperMutant::operator=(SuperMutant const& src) {
	if (this != &src)
	{
		this->_hp = src._hp;
		this->_type = src._type;
	}
	return *this;
}

void	SuperMutant::takeDamage(int amount) {
	amount -= 3;
	if (amount < 0)
		return ;
	this->_hp -= amount;
	if (this->_hp < 0)
		this->_hp = 0;
}
