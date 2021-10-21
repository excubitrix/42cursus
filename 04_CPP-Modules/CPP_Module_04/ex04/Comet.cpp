#include "Comet.hpp"

Comet::Comet(void) : _name("Comet") {
}

Comet::Comet(Comet const& src) : _name(src._name) {
}

Comet::~Comet(void) {
}

Comet&	Comet::operator=(Comet const& src) {
	if (this != &src)
		;
	return *this;
}

std::string	Comet::beMined(DeepCoreMiner *) const {
	return "Meium";
}

std::string	Comet::beMined(StripMiner *) const {
	return "Tartarite";
}

std::string	Comet::getName(void) const {
	return this->_name;
}
