#include "SuperTrap.hpp"

SuperTrap::SuperTrap(std::string name) : ClapTrap(name, "SUP3R-TP"), FragTrap(name), NinjaTrap(name) {
	std::cout << "SuperTrap constructor called: " << "<" + this->_name + "> "
			  << this->_announcement(rand() % 2) << std::endl;
	this->_hitPoints = 100;
	this->_maxHitPoints = 100;
	this->_engeryPoints = 120;
	this->_maxEngeryPoints = 120;
	this->_meleeAttackDamage = 60;
	this->_rangedAttackDamage = 20;
	this->_armorDamageReduction = 5;
	srand(time(NULL));
}

SuperTrap::SuperTrap(SuperTrap const& src) : ClapTrap(src._name, src.getType()), FragTrap(_name), NinjaTrap(_name) {
	*this = src;
}

SuperTrap::~SuperTrap(void) {
	std::cout << "SuperTrap destructor called: " << "<" + this->_name + "> "
			  << this->_farewell(rand() % 2) << std::endl;
}

SuperTrap&	SuperTrap::operator=(SuperTrap const& src) {
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

void	SuperTrap::meleeAttack(std::string const & target) {
	NinjaTrap::meleeAttack(target);
}

void	SuperTrap::rangedAttack(std::string const & target) {
	FragTrap::rangedAttack(target);
}

std::string	SuperTrap::_announcement(int const i) const {
	if (i)
		return FragTrap::_announcement[rand() % 6];
	return NinjaTrap::_announcement[rand() % 6];
}

std::string	SuperTrap::_farewell(int const i) const {
	if (i)
		return FragTrap::_farewell[rand() % 3];
	return NinjaTrap::_farewell[rand() % 3];
}

SuperTrap::SuperTrap(void) : ClapTrap(std::string()), FragTrap(std::string()), NinjaTrap(std::string()) {
}
