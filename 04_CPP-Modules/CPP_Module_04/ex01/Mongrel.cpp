#include "Mongrel.hpp"

Mongrel::Mongrel(void) : Enemy(55, "Mongrel") {
	std::cout << "Grrrrr..." << std::endl;
}

Mongrel::Mongrel(Mongrel const& src) : Enemy(src._hp, src._type) {
}

Mongrel::~Mongrel(void) {
	std::cout << "Arf..." << std::endl;
}

Mongrel&	Mongrel::operator=(Mongrel const& src) {
	if (this != &src)
	{
		this->_hp = src._hp;
		this->_type = src._type;
	}
	return *this;
}
