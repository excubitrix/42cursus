#include "Decrement.hpp"

Decrement::Decrement(void) {
}

Decrement::Decrement(Decrement const &src) {
	*this = src;
}

Decrement::~Decrement(void) {
}

Decrement& Decrement::operator=(Decrement const& src) {
	if (this != &src)
		;
	return *this;
}

IInstruction*	Decrement::clone(void) {
	return new Decrement();
}

void	Decrement::execute(MindOpen& mo) {
	mo.decrement();
}
