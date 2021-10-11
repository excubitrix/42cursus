#include "DeepCoreMiner.hpp"

DeepCoreMiner::DeepCoreMiner(void) {
}

DeepCoreMiner::DeepCoreMiner(DeepCoreMiner const& src) {
	*this = src;
}

DeepCoreMiner::~DeepCoreMiner(void) {
}

DeepCoreMiner&	DeepCoreMiner::operator=(DeepCoreMiner const& src) {
	if (this != &src)
		;
	return *this;
}

void	DeepCoreMiner::mine(IAsteroid* target) {
	if (target)
		std::cout << "* mining deep... got " << target->beMined(this) << "! *" << std::endl;
}
