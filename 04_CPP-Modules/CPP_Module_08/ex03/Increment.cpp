#include "Increment.hpp"

Increment::Increment(void) {
}

Increment::Increment(Increment const &src) {
	*this = src;
}

Increment::~Increment(void) {
}

Increment& Increment::operator=(Increment const& src) {
	if (this != &src)
		;
	return *this;
}

IInstruction*	Increment::clone(void) {
	return new Increment();
}

void	Increment::execute(MindOpen& mo) {
	mo.increment();
}
