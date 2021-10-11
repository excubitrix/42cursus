#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target) : Form("Robotomy Request", 72, 45), _target(target) {
	srand(time(NULL));
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const& src) : Form("Robotomy Request", 72, 45), _target(src._target) {
	*this = src;
}

RobotomyRequestForm::~RobotomyRequestForm(void) {
}

RobotomyRequestForm&	RobotomyRequestForm::operator=(RobotomyRequestForm const& src) {
	if (this != &src)
		this->_target = src._target;
	return *this;
}

std::string	RobotomyRequestForm::getTarget(void) const {
	return this->_target;
}

void	RobotomyRequestForm::action(void) const {
	std::cout << "Vvvvvvvrrrr...Riz...Riz...VVvvVvrrrr...Riz..." << std::endl;
	if ((rand() % 100) > 50)
		std::cout << "Robotomization of " << this->_target << " was a success!" << std::endl;
	else
		std::cout << "Robotomization of " << this->_target << " has failed." << std::endl;
}
