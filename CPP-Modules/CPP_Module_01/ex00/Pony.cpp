#include "Pony.hpp"

Pony::Pony(std::string name) : _name(name.substr(0, 11)) {
	std::cout << GREEN "Parameter contructor called: " << this->_name << " is now in your care." RESET << std::endl;
	this->_engery = 100.;
	this->_weight = 400.;
	this->_stamina = 50.;
	this->_speed = 50.;
	this->_dressage = 50.;
	this->_gallop = 50.;
	this->_trot = 50.;
	this->_jumping = 50.;
}

Pony::Pony(void) {
	std::cout << GREEN "Default contructor called: " << this->_name << " is now in your care." RESET << std::endl;
	this->_name = "Pony";
	this->_engery = 100.;
	this->_weight = 400.;
	this->_stamina = 50.;
	this->_speed = 50.;
	this->_dressage = 50.;
	this->_gallop = 50.;
	this->_trot = 50.;
	this->_jumping = 50.;
}

Pony::~Pony(void) {
	std::cout << MAGENTA "Destructor called: " << this->_name << " retired." RESET << std::endl;
}

void	Pony::_restore_energy(float amount) {
	this->_engery += amount;
	if (this->_engery > 100.)
		this->_engery = 100.;
}

void	Pony::eat(void) {
	this->_restore_energy(30.);
	std::cout << this->_name << " has eaten." << std::endl;
	if ((this->_weight += 12.) > 440.)
		std::cout << this->_name << " is overweight." << std::endl;
}

void	Pony::sleep(void) {
	this->_restore_energy(100.);
	std::cout << this->_name << " has slept." << std::endl;
	if ((this->_weight -= 4.) < 360.)
		std::cout << this->_name << " is underweight." << std::endl;
}

bool	Pony::rename(std::string new_name) {
	if (new_name.length() < 12)
	{
		std::cout << this->_name + " has been renamed to " + new_name + "." << std::endl;
		this->_name = new_name;
	}
	else
	{
		std::cout << "\"" + new_name + "\" is too long a name." << std::endl;
		return (false);
	}
	return (true);
}

bool	Pony::train(std::string skill, int duration) {
	float	new_value;

	if ((new_value = this->_engery - (15. * duration)) > 5.)
		this->_engery = new_value;
	else
	{
		std::cout << this->_name
				  << " does not have enough energy to train for "
				  << duration << " hours."
				  << std::endl;
		return (false);
	}
	std::cout << this->_name << " has trained their "
			  << skill << " skill for " << duration << " hours." << std::endl;
	if ((new_value = _get_skill(skill) + (0.5 * duration)) >= 100.)
		std::cout << this->_name << " has maxed out their "
				  << skill << " skill." << std::endl;
	if ((this->_weight -= 1.5 * duration) < 360.)
		std::cout << this->_name << " is underweight." << std::endl;
	_set_skill(skill, new_value);
	return (true);
}

void	Pony::display_stats(void) const {
	std::cout << "-------------------------------" << std::endl
			  << "|" << std::setw(13) << this->_name << "'s Stats:" << std::setw(8) << "|" << std::endl
			  << "|-----------------------------|" << std::endl;
	std::cout << "|" << std::setw(13) << "Engery" << ": " << std::setw(5) << this->_engery << " %" << std::setw(8) << "|" << std::endl;
	std::cout << "|" << std::setw(13) << "Weight" << ": " << std::setw(5) << this->_weight << " lbs" << std::setw(6) << "|" << std::endl;
	std::cout << "|- - - - - - - - - - - - - - -|" << std::endl;
	std::cout << "|" << std::setw(13) << "Stamina" << ": " << std::setw(5) << this->_stamina << " %" << std::setw(8) << "|" << std::endl;
	std::cout << "|" << std::setw(13) << "Speed" << ": " << std::setw(5) << this->_speed << " %" << std::setw(8) << "|" << std::endl;
	std::cout << "|" << std::setw(13) << "Dressage" << ": " << std::setw(5) << this->_dressage << " %" << std::setw(8) << "|" << std::endl;
	std::cout << "|" << std::setw(13) << "Gallop" << ": " << std::setw(5) << this->_gallop << " %" << std::setw(8) << "|" << std::endl;
	std::cout << "|" << std::setw(13) << "Trot" << ": " << std::setw(5) << this->_trot << " %" << std::setw(8) << "|" << std::endl;
	std::cout << "|" << std::setw(13) << "Jumping" << ": " << std::setw(5) << this->_jumping << " %" << std::setw(8) << "|" << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

float	Pony::_get_skill(std::string skill) const {
	if (!skill.compare("stamina"))
		return this->_stamina;
	if (!skill.compare("speed"))
		return this->_speed;
	if (!skill.compare("dressage"))
		return this->_dressage;
	if (!skill.compare("gallop"))
		return this->_gallop;
	if (!skill.compare("trot"))
		return this->_trot;
	if (!skill.compare("jumping"))
		return this->_jumping;
	std::cout << "Error: No such skill." << std::endl;
	return 0.;
}

void	Pony::_set_skill(std::string skill, float new_value) {
	if (new_value > 100.)
		new_value = 100.;
	if (!skill.compare("stamina"))
		this->_stamina = new_value;
	if (!skill.compare("speed"))
		this->_speed = new_value;
	if (!skill.compare("dressage"))
		this->_dressage = new_value;
	if (!skill.compare("gallop"))
		this->_gallop = new_value;
	if (!skill.compare("trot"))
		this->_trot = new_value;
	if (!skill.compare("jumping"))
		this->_jumping = new_value;
}
