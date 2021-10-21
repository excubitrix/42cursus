#include "Character.hpp"

Character::Character(std::string const& name) : _name(name), _ap(40), _weapon(NULL) {
}

Character::Character(Character const& src) : _name(src._name), _ap(src._ap), _weapon(src._weapon) {
}

Character::~Character(void) {
}

Character&	Character::operator=(Character const& src) {
	if (this != &src)
	{
		this->_name = src._name;
		this->_ap = src._ap;
		this->_weapon = src._weapon;
	}
	return *this;
}

void	Character::recoverAP(void) {
	this->_ap += 10;
	if (this->_ap > 40)
		this->_ap = 40;
}

void	Character::equip(AWeapon* weapon) {
	this->_weapon = weapon;
}

void	Character::attack(Enemy* enemy) {
	if (!enemy)
		return ;
	if (this->_weapon)
	{
		if (this->_ap < this->_weapon->getAPCost())
		{
			std::cout << this->_name + " does not have enough AP" << std::endl;
			return ;
		}
		std::cout << this->_name + " attacks " + enemy->getType() + " with a " + this->_weapon->getName() << std::endl;
		this->_weapon->attack();
		enemy->takeDamage(this->_weapon->getDamage());
		if (enemy->getHP() == 0)
			delete enemy;
		this->_ap -= this->_weapon->getAPCost();
	}
	else
		std::cout << this->_name + " does not have a weapon equipped" << std::endl;
}

std::string	Character::getName(void) const {
	return this->_name;
}

int	Character::getAP(void) const {
	return this->_ap;
}

AWeapon*	Character::getWeapon(void) const {
	return this->_weapon;
}

Character::Character(void) {
}

std::ostream&	operator<<(std::ostream& out, Character const& src) {
	out << src.getName() << " has " << src.getAP() << " AP and ";
	if (src.getWeapon() != NULL)
		out << "whields a " << src.getWeapon()->getName() << std::endl;
	else
		out << "is unarmed" << std::endl;
	return out;
}
