#include "Write.hpp"

Write::Write(void) {
}

Write::Write(Write const &src) {
	*this = src;
}

Write::~Write(void) {
}

Write& Write::operator=(Write const& src) {
	if (this != &src)
		;
	return *this;
}

IInstruction*	Write::clone(void) {
	return new Write();
}

void	Write::execute(MindOpen& mo) {
	mo.writeData();
}
