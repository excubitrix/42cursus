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

FragTrap::FragTrap(std::string name) : _name(name), _hitPoints(100), _maxHitPoints(100), _engeryPoints(100),
		_maxEngeryPoints(100), _level(1), _meleeAttackDamage(30), _rangedAttackDamage(20), _armorDamageReduction(5) {
	std::cout << "FragTrap constructor called: " << "<" + this->_name + "> "
			  << this->_announcement[rand() % 6] << std::endl;
	srand(time(NULL));
}

FragTrap::FragTrap(FragTrap const& src) {
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
	std::cout << "FR4G-TP " + this->_name + " attacks "
			  << target << ", causing " << this->_meleeAttackDamage
			  << " points of damage FragTrap-style!" << std::endl;
}

void	FragTrap::rangedAttack(std::string const & target) {
	std::cout << "FR4G-TP " + this->_name + " attacks " << target
			  << " at range, causing " << this->_rangedAttackDamage
			  << " points of damage FragTrap-style!" << std::endl;
}

void	FragTrap::takeDamage(unsigned int amount) {
	amount -= this->_armorDamageReduction;
	this->_hitPoints -= amount;
	if (this->_hitPoints <= 0)
	{
		amount += this->_hitPoints;
		this->_hitPoints = 0;
		std::cout << "FR4G-TP " + this->_name + " takes " << amount
				  << " points of fatal damage!" << std::endl;
	}
	else
		std::cout << "FR4G-TP " + this->_name + " takes " << amount
				  << " points of damage!" << std::endl;
}

void	FragTrap::beRepaired(unsigned int amount) {
	this->_hitPoints += amount;
	if (this->_hitPoints > this->_maxHitPoints)
	{
		amount -= (this->_hitPoints % this->_maxHitPoints);
		this->_hitPoints = this->_maxHitPoints;
	}
	std::cout << "FR4G-TP " + this->_name + " restores " << amount
			  << " points of damage!" << std::endl;
}

void	FragTrap::vaulthunter_dot_exe(std::string const & target) {
	if (this->_engeryPoints < 25)
		std::cout << "FR4G-TP " + this->_name + " is out of energy." << std::endl;
	else
	{
		this->_engeryPoints -= 25;
		std::cout << "FR4G-TP " + this->_name << this->_specialAttack[rand() % 5] << target
				  << ", causing 50 points of damage!" << std::endl;
	}
}

FragTrap::FragTrap(void) {
}
