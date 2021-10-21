#include "LoopEnd.hpp"

LoopEnd::LoopEnd(void) {
}

LoopEnd::LoopEnd(LoopEnd const &src) {
	*this = src;
}

LoopEnd::~LoopEnd(void) {
}

LoopEnd& LoopEnd::operator=(LoopEnd const& src) {
	if (this != &src)
		;
	return *this;
}

IInstruction*	LoopEnd::clone(void) {
	return new LoopEnd();
}

void	LoopEnd::execute(MindOpen& mo) {
	if (mo.getData())
		mo.repeat();
}
