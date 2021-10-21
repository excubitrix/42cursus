#include "Dragon.hpp"

Dragon::Dragon(void) : Enemy(350, "Dragon") {
	std::cout << "* ROOOAAAARRRR! *" << std::endl;
}

Dragon::Dragon(Dragon const& src) : Enemy(src._hp, src._type) {
}

Dragon::~Dragon(void) {
	std::cout << "* wince *" << std::endl;
}

Dragon&	Dragon::operator=(Dragon const& src) {
	if (this != &src)
	{
		this->_hp = src._hp;
		this->_type = src._type;
	}
	return *this;
}

void	Dragon::takeDamage(int amount) {
	amount -= 30;
	if (amount < 0)
		return ;
	this->_hp -= amount;
	if (this->_hp < 0)
		this->_hp = 0;
}
