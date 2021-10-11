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

ScavTrap::ScavTrap(std::string name) : ClapTrap(name, "SC4V-TP") {
	std::cout << "ScavTrap constructor called: " << "<" + this->_name + "> "
			  << this->_announcement[rand() % 6] << std::endl;
	this->_hitPoints = 100;
	this->_maxHitPoints = 100;
	this->_engeryPoints = 50;
	this->_maxEngeryPoints = 50;
	this->_meleeAttackDamage = 20;
	this->_rangedAttackDamage = 15;
	this->_armorDamageReduction = 3;
	srand(time(NULL));
}

ScavTrap::ScavTrap(ScavTrap const& src) : ClapTrap(src._name, src.getType()) {
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
	std::cout << this->getType() + " " + this->_name + " attacks "
			  << target << ", causing " << this->_meleeAttackDamage
			  << " points of damage ScavTrap-style!" << std::endl;
}

void	ScavTrap::rangedAttack(std::string const & target) {
	std::cout << this->getType() + " " + this->_name + " attacks " << target
			  << " at range, causing " << this->_rangedAttackDamage
			  << " points of damage ScavTrap-style!" << std::endl;
}

void	ScavTrap::challengeNewcomer(void) {
	std::cout << this->getType() + " " + this->_name + " challenges " << this->_newcomer[rand() % 5] << "."
			  << " <" + this->_name + "> " << this->_prompt[rand() % 5] << std::endl;
}

ScavTrap::ScavTrap(void) : ClapTrap(std::string()) {
}
