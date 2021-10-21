#include "Read.hpp"

Read::Read(void) {
}

Read::Read(Read const &src) {
	*this = src;
}

Read::~Read(void) {
}

Read& Read::operator=(Read const& src) {
	if (this != &src)
		;
	return *this;
}

IInstruction*	Read::clone(void) {
	return new Read();
}

void	Read::execute(MindOpen& mo) {
	mo.readData();
}
