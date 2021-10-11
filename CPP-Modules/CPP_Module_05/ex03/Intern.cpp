#include "Intern.hpp"

std::string const	Intern::_formName[6] = {
	"shrubbery creation",
	"Shrubbery Creation",
	"robotomy request",
	"Robotomy Request",
	"presidential pardon",
	"Presidential Pardon"
};

Intern::functionPtr const	Intern::_form[6] = {
	&Intern::createShrubberyCreationForm,
	&Intern::createShrubberyCreationForm,
	&Intern::createRobotomyRequestForm,
	&Intern::createRobotomyRequestForm,
	&Intern::createPresidentialPardonForm,
	&Intern::createPresidentialPardonForm
};

Intern::Intern(void) {
}

Intern::Intern(Intern const& src) {
	*this = src;
}

Intern::~Intern(void) {
}

Intern&	Intern::operator=(Intern const& src) {
	if (this != &src)
		;
	return *this;
}

const char*	Intern::UnknownFormException::what() const throw() {
	return RED "Unknown form" RESET;
}

Form*	Intern::createShrubberyCreationForm(std::string const& target) {
	return new ShrubberyCreationForm(target);
}

Form*	Intern::createRobotomyRequestForm(std::string const& target) {
	return new RobotomyRequestForm(target);
}

Form*	Intern::createPresidentialPardonForm(std::string const& target) {
	return new PresidentialPardonForm(target);
}

Form*	Intern::makeForm(std::string const& name, std::string const& target) {
	for (int i = 0; i < 6; i++)
	{
		if (!name.compare(this->_formName[i]))
		{
			Form* form = (this->*_form[i])(target);
			std::cout << PUKE_GREEN << "Intern " << RESET << GREEN << "creates" << RESET << " a " << CYAN
					  << form->getName() << " Form " << YELLOW << "(s.grade " << form->getSignGrade()
					  << ", ex.grade " << form->getExecGrade() << ", unsigned)" << RESET << ", targeted on "
					  << BLUE << target << RESET << std::endl;
			return form;
		}
	}
	std::cout << PUKE_GREEN << "Intern " << RESET << "is unable to create the requested form because: ";
	throw UnknownFormException();
}
