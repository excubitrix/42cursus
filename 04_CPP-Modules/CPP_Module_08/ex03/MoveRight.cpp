#include "MoveRight.hpp"

MoveRight::MoveRight(void) {
}

MoveRight::MoveRight(MoveRight const &src) {
	*this = src;
}

MoveRight::~MoveRight(void) {
}

MoveRight& MoveRight::operator=(MoveRight const& src) {
	if (this != &src)
		;
	return *this;
}

IInstruction*	MoveRight::clone(void) {
	return new MoveRight();
}

void	MoveRight::execute(MindOpen& mo) {
	mo.moveRight();
}
