#include "Asteroid.hpp"

Asteroid::Asteroid(void) : _name("Asteroid") {
}

Asteroid::Asteroid(Asteroid const& src) : _name(src._name) {
}

Asteroid::~Asteroid(void) {
}

Asteroid&	Asteroid::operator=(Asteroid const& src) {
	if (this != &src)
		;
	return *this;
}

std::string	Asteroid::beMined(DeepCoreMiner *) const {
	return "Dragonite";
}

std::string	Asteroid::beMined(StripMiner *) const {
	return "Flavium";
}

std::string	Asteroid::getName(void) const {
	return this->_name;
}

