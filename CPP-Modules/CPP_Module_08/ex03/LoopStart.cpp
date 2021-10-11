#include "LoopStart.hpp"

LoopStart::LoopStart(void) {
}

LoopStart::LoopStart(LoopStart const &src) {
	*this = src;
}

LoopStart::~LoopStart(void) {
}

LoopStart& LoopStart::operator=(LoopStart const& src) {
	if (this != &src)
		;
	return *this;
}

IInstruction*	LoopStart::clone(void) {
	return new LoopStart();
}

void	LoopStart::execute(MindOpen& mo) {
	if (!mo.getData())
		mo.next();
}
