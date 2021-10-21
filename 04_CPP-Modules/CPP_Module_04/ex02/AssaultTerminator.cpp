#include "AssaultTerminator.hpp"

AssaultTerminator::AssaultTerminator(void) {
	std::cout << "* teleports from space *" << std::endl;
}

AssaultTerminator::AssaultTerminator(AssaultTerminator const& src) {
	*this = src;
}

AssaultTerminator::~AssaultTerminator(void) {
	std::cout << "I’ll be back..." << std::endl;
}

AssaultTerminator&	AssaultTerminator::operator=(AssaultTerminator const& src) {
	if (this != &src)
		;
	return *this;
}

ISpaceMarine*	AssaultTerminator::clone(void) const {
	return new AssaultTerminator(*this);
}

void	AssaultTerminator::battleCry(void) const {
	std::cout << "This code is unclean. PURIFY IT!" << std::endl;
}

void	AssaultTerminator::rangedAttack(void) const {
	std::cout << "* does nothing *" << std::endl;
}

void	AssaultTerminator::meleeAttack(void) const {
	std::cout << "* attacks with chainfists *" << std::endl;
}
