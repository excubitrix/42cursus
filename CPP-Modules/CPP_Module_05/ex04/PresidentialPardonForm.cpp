#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target) : Form("Presidential Pardon", 25, 5), _target(target) {
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const& src) : Form("Presidential Pardon", 25, 5), _target(src._target) {
	*this = src;
}

PresidentialPardonForm::~PresidentialPardonForm(void) {
}

PresidentialPardonForm&	PresidentialPardonForm::operator=(PresidentialPardonForm const& src) {
	if (this != &src)
		this->_target = src._target;
	return *this;
}

std::string	PresidentialPardonForm::getTarget(void) const {
	return this->_target;
}

void	PresidentialPardonForm::action(void) const {
	std::cout << this->_target << " has been pardoned by Zafod Beeblebrox." << std::endl;
}
