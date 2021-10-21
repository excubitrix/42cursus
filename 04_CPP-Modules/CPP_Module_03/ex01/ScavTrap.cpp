#include "ScavTrap.hpp"

std::string const	ScavTrap::_announcement[6] = {
	"I can take ya!.. I think.",
	"Ow, what was that for?",
	"Oh, it's on now!",
	"You wanna fight with me?! Put 'em up!.. Put 'em up?",
	"A million baddies, and you wanna hit me? Aww!",
	"Now? But I... I just... okay..."
};

std::string const	ScavTrap::_farewell[3] = {
	"No, nononono NO!",
	"I have many regrets!",
	"I'm too pretty to die!"
};

std::string const	ScavTrap::_prompt[5] = {
	BLUE "You versus me! Me versus you! Either way!" RESET,
	RED "I will prove to you my robotic superiority!" RESET,
	MAGENTA "Dance battle! Or, you know... regular battle." RESET,
	YELLOW "I challenge you!" RESET,
	GREEN "Care to have a friendly duel?" RESET
};

std::string const	ScavTrap::_newcomer[5] = {
	GREEN "giant green gelatinous cube" RESET,
	RED "T. rex" RESET,
	YELLOW "owlbear" RESET,
	MAGENTA "little girl" RESET,
	BLUE "Slime" RESET
};

ScavTrap::ScavTrap(std::string name) : _name(name), _hitPoints(100), _maxHitPoints(100), _engeryPoints(50),
		_maxEngeryPoints(50), _level(1), _meleeAttackDamage(20), _rangedAttackDamage(15), _armorDamageReduction(3) {
	std::cout << "ScavTrap constructor called: " << "<" + this->_name + "> "
			  << this->_announcement[rand() % 6] << std::endl;
	srand(time(NULL));
}

ScavTrap::ScavTrap(ScavTrap const& src) {
	*this = src;
}

ScavTrap::~ScavTrap(void) {
	std::cout << "ScavTrap destructor called: " << "<" + this->_name + "> "
			  << this->_farewell[rand() % 3] << std::endl;
}

ScavTrap&	ScavTrap::operator=(ScavTrap const& src) {
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

void	ScavTrap::meleeAttack(std::string const & target) {
	std::cout << "SC4V-TP " + this->_name + " attacks "
			  << target << ", causing " << this->_meleeAttackDamage
			  << " points of damage ScavTrap-style!" << std::endl;
}

void	ScavTrap::rangedAttack(std::string const & target) {
	std::cout << "SC4V-TP " + this->_name + " attacks " << target
			  << " at range, causing " << this->_rangedAttackDamage
			  << " points of damage ScavTrap-style!" << std::endl;
}

void	ScavTrap::takeDamage(unsigned int amount) {
	amount -= this->_armorDamageReduction;
	this->_hitPoints -= amount;
	if (this->_hitPoints <= 0)
	{
		amount += this->_hitPoints;
		this->_hitPoints = 0;
		std::cout << "SC4V-TP " + this->_name + " takes " << amount
				  << " points of fatal damage!" << std::endl;
	}
	else
		std::cout << "SC4V-TP " + this->_name + " takes " << amount
				  << " points of damage!" << std::endl;
}

void	ScavTrap::beRepaired(unsigned int amount) {
	this->_hitPoints += amount;
	if (this->_hitPoints > this->_maxHitPoints)
	{
		amount -= (this->_hitPoints % this->_maxHitPoints);
		this->_hitPoints = this->_maxHitPoints;
	}
	std::cout << "SC4V-TP " + this->_name + " restores " << amount
			  << " points of damage!" << std::endl;
}

void	ScavTrap::challengeNewcomer(void) {
	std::cout << "SC4V-TP " + this->_name + " challenges " << this->_newcomer[rand() % 5] << "."
			  << " <" + this->_name + "> " << this->_prompt[rand() % 5] << std::endl;
}

ScavTrap::ScavTrap(void) {
}
