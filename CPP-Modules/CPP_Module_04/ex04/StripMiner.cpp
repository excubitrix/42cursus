#include "StripMiner.hpp"

StripMiner::StripMiner(void) {
}

StripMiner::StripMiner(StripMiner const& src) {
	*this = src;
}

StripMiner::~StripMiner(void) {
}

StripMiner&	StripMiner::operator=(StripMiner const& src) {
	if (this != &src)
		;
	return *this;
}

void	StripMiner::mine(IAsteroid* target) {
	if (target)
		std::cout << "* strip mining... got " << target->beMined(this) << "! *" << std::endl;
}
