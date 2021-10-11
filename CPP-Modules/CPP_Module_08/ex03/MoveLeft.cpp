#include "MoveLeft.hpp"

MoveLeft::MoveLeft(void) {
}

MoveLeft::MoveLeft(MoveLeft const &src) {
	*this = src;
}

MoveLeft::~MoveLeft(void) {
}

MoveLeft& MoveLeft::operator=(MoveLeft const& src) {
	if (this != &src)
		;
	return *this;
}

IInstruction*	MoveLeft::clone(void) {
	return new MoveLeft();
}

void	MoveLeft::execute(MindOpen& mo) {
	mo.moveLeft();
}
