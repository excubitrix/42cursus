#include "Character.hpp"

Character::Character(std::string const& name) : _name(name) {
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = NULL;
}

Character::Character(Character const& src) {
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = NULL;
	*this = src;
}

Character::~Character(void) {
	for (int i = 0; i < 4; i++)
		if (this->_inventory[i])
			delete this->_inventory[i];
}

Character&	Character::operator=(Character const& src) {
	if (this != &src)
	{
		this->_name = src._name;
		for (int i = 0; i < 4; i++)
		{
			if (this->_inventory[i])
				delete this->_inventory[i];
			if (src._inventory[i])
				this->_inventory[i] = src._inventory[i]->clone();
		}
	}
	return *this;
}

std::string const& Character::getName(void) const {
	return this->_name;
}

void Character::equip(AMateria* m) {
	for (int i = 0; i < 4; i++)
	{
		if (this->_inventory[i] == m)
			return ;
		if (!this->_inventory[i])
		{
			this->_inventory[i] = m;
			return ;
		}
	}
}

void Character::unequip(int idx) {
	if (this->_inventory[idx])
		this->_inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target) {
	if (this->_inventory[idx])
		this->_inventory[idx]->use(target);
}

Character::Character(void) {
}
