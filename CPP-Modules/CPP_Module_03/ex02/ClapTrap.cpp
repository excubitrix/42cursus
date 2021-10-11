#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name) : _name(name), _level(1), _type("CL4P-TP") {
	std::cout << "ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name, std::string type) : _name(name), _level(1), _type(type) {
	std::cout << "ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const& src) {
	*this = src;
}

ClapTrap::~ClapTrap(void) {
	std::cout << "ClapTrap destructor called" << std::endl;
}

ClapTrap&	ClapTrap::operator=(ClapTrap const& src) {
	if (this != &src)
	{
		this->_name = src._name;
		this->_hitPoints = src._hitPoints;
		this->_maxHitPoints = src._maxHitPoints;
		this->_engeryPoints = src._engeryPoints;
		this->_maxEngeryPoints = src._maxEngeryPoints;
		this->_level = src._level;
		this->_meleeAttackDamage = src._meleeAttackDamage ;
		this->_rangedAttackDamage = src._rangedAttackDamage;
		this->_armorDamageReduction = src._armorDamageReduction;
	}
	return *this;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	amount -= this->_armorDamageReduction;
	this->_hitPoints -= amount;
	if (this->_hitPoints <= 0)
	{
		amount += this->_hitPoints;
		this->_hitPoints = 0;
		std::cout << this->_type + " " + this->_name + " takes " << amount
				  << " points of fatal damage!" << std::endl;
	}
	else
		std::cout << this->_type + " " + this->_name + " takes " << amount
				  << " points of damage!" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	this->_hitPoints += amount;
	if (this->_hitPoints > this->_maxHitPoints)
	{
		amount -= (this->_hitPoints % this->_maxHitPoints);
		this->_hitPoints = this->_maxHitPoints;
	}
	std::cout << this->_type + " " + this->_name + " restores " << amount
			  << " points of damage!" << std::endl;
}

std::string const	ClapTrap::getName(void) const {
	return this->_name;
}

std::string const	ClapTrap::getType(void) const {
	return this->_type;
}

ClapTrap::ClapTrap(void) {
}
