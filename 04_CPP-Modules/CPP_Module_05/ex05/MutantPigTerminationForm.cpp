#include "MutantPigTerminationForm.hpp"

MutantPigTerminationForm::MutantPigTerminationForm(std::string target) : Form("Mutant Pig Termination", 130, 50), _target(target) {
}

MutantPigTerminationForm::MutantPigTerminationForm(MutantPigTerminationForm const& src) : Form("Mutant Pig Termination", 130, 50), _target(src._target) {
	*this = src;
}

MutantPigTerminationForm::~MutantPigTerminationForm(void) {
}

MutantPigTerminationForm&	MutantPigTerminationForm::operator=(MutantPigTerminationForm const& src) {
	if (this != &src)
		this->_target = src._target;
	return *this;
}

std::string	MutantPigTerminationForm::getTarget(void) const {
	return this->_target;
}

void	MutantPigTerminationForm::action(void) const {
	std::cout << "That'll do, " << this->_target << ". That'll do..." << std::endl;
}
