#include "NinjaTrap.hpp"

std::string const	NinjaTrap::_announcement[6] = {
	"I am a tornado of death and bullets!",
	"Stop me before I kill again, except don't!",
	"Hehehehe, mwaa ha ha ha, MWAA HA HA HA!",
	"I'm a robot ninja...",
	"There is no way this ends badly!",
	"This is why I was built!"
};

std::string const	NinjaTrap::_farewell[3] = {
	"Robot down!",
	"Good thing I don't have a soul!",
	"I'm leaking!"
};

NinjaTrap::NinjaTrap(std::string name) : ClapTrap(name, "N1NJ4-TP") {
	std::cout << "NinjaTrap constructor called: " << "<" + this->_name + "> "
			  << this->_announcement[rand() % 6] << std::endl;
	this->_hitPoints = 60;
	this->_maxHitPoints = 60;
	this->_engeryPoints = 120;
	this->_maxEngeryPoints = 120;
	this->_meleeAttackDamage = 60;
	this->_rangedAttackDamage = 5;
	this->_armorDamageReduction = 0;
	srand(time(NULL));
}

NinjaTrap::NinjaTrap(NinjaTrap const& src) : ClapTrap(src._name, src.getType()) {
	*this = src;
}

NinjaTrap::~NinjaTrap(void) {
	std::cout << "NinjaTrap destructor called: " << "<" + this->_name + "> "
			  << this->_farewell[rand() % 3] << std::endl;
}

NinjaTrap&	NinjaTrap::operator=(NinjaTrap const& src) {
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

void	NinjaTrap::meleeAttack(std::string const & target) {
	std::cout << this->getType() + " " + this->_name + " attacks "
			  << target << ", causing " << this->_meleeAttackDamage
			  << " points of damage NinjaTrap-style!" << std::endl;
}

void	NinjaTrap::rangedAttack(std::string const & target) {
	std::cout << this->getType() + " " + this->_name + " attacks " << target
			  << " at range, causing " << this->_rangedAttackDamage
			  << " points of damage NinjaTrap-style!" << std::endl;
}

void	NinjaTrap::ninjaShoebox(ClapTrap& ref) {
	if (this->_engeryPoints < 20)
		std::cout << this->getType() + " " + this->_name + " is out of energy." << std::endl;
	else
	{
		std::cout << this->getType() + " " + this->_name + " asks " + ref.getName()
				  << ". <" + this->_name + "> Are you my father?" << std::endl;
		this->_engeryPoints -= 20;
	}
}

void	NinjaTrap::ninjaShoebox(FragTrap& ref) {
	if (this->_engeryPoints < 20)
		std::cout << this->getType() + " " + this->_name + " is out of energy." << std::endl;
	else
	{
		std::cout << this->getType() + " " + this->_name + " screams at " + ref.getName()
				  << ". <" + this->_name + "> I AM ON FIRE!!! OH GOD, PUT ME OUT!!!" << std::endl;
		this->_engeryPoints -= 20;
	}
}

void	NinjaTrap::ninjaShoebox(ScavTrap& ref) {
	if (this->_engeryPoints < 20)
		std::cout << this->getType() + " " + this->_name + " is out of energy." << std::endl;
	else
	{
		std::cout << this->getType() + " " + this->_name + " challenges " + ref.getName()
				  << ". <" + this->_name + "> I challenge thee." << std::endl;
		this->_engeryPoints -= 20;
	}
}

void	NinjaTrap::ninjaShoebox(NinjaTrap& ref) {
	if (this->_engeryPoints < 20)
		std::cout << this->getType() + " " + this->_name + " is out of energy." << std::endl;
	else
	{
		std::cout << this->getType() + " " + this->_name + " cloaks himself. <" + this->_name
				  << "> I'm invisible! <" + ref.getName() + "> I'm invisible, too! <"
				  << this->_name + "> Well, this is awkward..." << std::endl;
		this->_engeryPoints -= 20;
	}
}

NinjaTrap::NinjaTrap(void) : ClapTrap(std::string()) {
}
