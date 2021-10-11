#include "FragTrap.hpp"

std::string const	FragTrap::_announcement[6] = {
	"Hey everybody! Check out my package!",
	"Let's get this party started!",
	"Glitching weirdness is a term of endearment, right?",
	"Recompiling my combat code!",
	"This time it'll be awesome, I promise!",
	"Look out everybody! Things are about to get awesome!"
};

std::string const	FragTrap::_farewell[3] = {
	"NOOO!",
	"Not fair! I wasn't ready.",
	"Argh arghargh death gurgle gurglegurgle urgh... death."
};

std::string const	FragTrap::_specialAttack[5] = {
	MAGENTA " throws a series of live grenades in the direction of " RESET,
	YELLOW " sings a terrible lullaby for " RESET,
	GREEN " requests a highfive from " RESET,
	RED " shoots lasers from its eyes at " RESET,
	BLUE " turns into a pirate ship and fires its cannons at " RESET
};

FragTrap::FragTrap(std::string name) : ClapTrap(name, "FR4G-TP") {
	std::cout << "FragTrap constructor called: " << "<" + this->_name + "> "
			  << this->_announcement[rand() % 6] << std::endl;
	this->_hitPoints = 100;
	this->_maxHitPoints = 100;
	this->_engeryPoints = 100;
	this->_maxEngeryPoints = 100;
	this->_meleeAttackDamage = 30;
	this->_rangedAttackDamage = 20;
	this->_armorDamageReduction = 5;
	srand(time(NULL));
}

FragTrap::FragTrap(FragTrap const& src) : ClapTrap(src._name, src.getType()) {
	*this = src;
}

FragTrap::~FragTrap(void) {
	std::cout << "FragTrap destructor called: " << "<" + this->_name + "> "
			  << this->_farewell[rand() % 3] << std::endl;
}

FragTrap&	FragTrap::operator=(FragTrap const& src) {
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

void	FragTrap::meleeAttack(std::string const & target) {
	std::cout << this->getType() + " " + this->_name + " attacks "
			  << target << ", causing " << this->_meleeAttackDamage
			  << " points of damage FragTrap-style!" << std::endl;
}

void	FragTrap::rangedAttack(std::string const & target) {
	std::cout << this->getType() + " " + this->_name + " attacks " << target
			  << " at range, causing " << this->_rangedAttackDamage
			  << " points of damage FragTrap-style!" << std::endl;
}

void	FragTrap::vaulthunter_dot_exe(std::string const & target) {
	if (this->_engeryPoints < 25)
		std::cout << this->getType() + " " + this->_name + " is out of energy." << std::endl;
	else
	{
		this->_engeryPoints -= 25;
		std::cout << this->getType() + " " + this->_name << this->_specialAttack[rand() % 5] << target
				  << ", causing 50 points of damage!" << std::endl;
	}
}

FragTrap::FragTrap(void) : ClapTrap(std::string()) {
}
