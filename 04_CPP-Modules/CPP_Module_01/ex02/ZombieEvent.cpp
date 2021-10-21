#include "ZombieEvent.hpp"

std::string	ZombieEvent::_type = "event";

ZombieEvent::ZombieEvent(void) {
	std::cout << "ZombieEvent default constructor called" << std::endl;
}

ZombieEvent::~ZombieEvent(void) {
	std::cout << "ZombieEvent destructor called" << std::endl;
}

void	ZombieEvent::setZombieType(std::string type) {
	this->_type = type;
}

Zombie*	ZombieEvent::newZombie(std::string name) {
	Zombie*	zombie = new Zombie(name, this->_type);
	return zombie;
}

std::string gen_random(const int len) {
	std::string tmp;
    std::string const alpha = "abcdefghijklmnopqrstuvwxyz";

	tmp.reserve(len);

	for (int i = 0; i < len; ++i)
		tmp += alpha[rand() % alpha.length()];
	tmp[0] = std::toupper(tmp[0]);

	return tmp;
}

Zombie*	randomChump(void) {    
	Zombie *random = new Zombie(gen_random(6), "random");
	random->announce();
	return random;
}
