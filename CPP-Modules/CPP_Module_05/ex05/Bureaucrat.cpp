#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat(std::string const name, int grade) : _name(name), _grade(grade) {
	if (this->_grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (this->_grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat(Bureaucrat const& src) : _name(src._name), _grade(src._grade) {
	if (this->_grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (this->_grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::~Bureaucrat(void) {
}

Bureaucrat&	Bureaucrat::operator=(Bureaucrat const& src) {
	if (this != &src)
		this->_grade = src._grade;
	return *this;
}

const char*	Bureaucrat::GradeTooHighException::what() const throw() {
	return RED "Grade too high" RESET;
}

const char*	Bureaucrat::GradeTooLowException::what() const throw() {
	return RED "Grade too low" RESET;
}

std::string const	Bureaucrat::getName(void) const {
	return this->_name;
}

int	Bureaucrat::getGrade(void) const {
	return this->_grade;
}

void	Bureaucrat::incrementGrade(void) {
	this->_grade--;
	if (this->_grade < 1)
		throw Bureaucrat::GradeTooHighException();

}

void	Bureaucrat::decrementGrade(void) {
	this->_grade++;
	if (this->_grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

void	Bureaucrat::signForm(Form& form) {
	if (!form.getStatus() && this->getGrade() <= form.getSignGrade())
		std::cout << HONEY << "Bureaucrat " << this->getName() << YELLOW << " (Grade " << this->getGrade() << ")" << RESET
				  << GREEN << " signs" << RESET << " a " << CYAN << form.getName() << " Form " << YELLOW << "(s.grade " << form.getSignGrade()
				  << ", ex.grade " << form.getExecGrade() << ", unsigned)" << RESET << ", targeted on " << BLUE << form.getTarget()
				  << RESET << std::endl;
	else
		std::cout << HONEY << "Bureaucrat " << this->getName() << YELLOW << " (Grade " << this->getGrade() << ")" << RESET
				  << " cannot " << GREEN << "sign" << RESET << " the " CYAN << form.getName() << " Form" << RESET " because: ";
	try
	{	
		form.beSigned(*this);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	Bureaucrat::executeForm(Form const& form) {
	if (form.getStatus() && this->getGrade() <= form.getExecGrade())
		std::cout << HONEY << "Bureaucrat " << this->getName() << YELLOW << " (Grade " << this->getGrade() << ")" << RESET
				  << MAGENTA << " executes" << RESET << " a " << CYAN << form.getName() << " Form "  << YELLOW << "(s.grade " << form.getSignGrade()
				  << ", ex.grade " << form.getExecGrade() << ", signed)" << RESET << ", targeted on " << BLUE << form.getTarget()
				  << RESET << std::endl;
	else
		std::cout << HONEY << "Bureaucrat " << this->getName() << YELLOW << " (Grade " << this->getGrade() << ")" << RESET
				  << " cannot " << MAGENTA << "execute" << RESET << " the " CYAN << form.getName() << " Form" << RESET " because: ";
	try
	{
		form.execute(*this);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

Bureaucrat::Bureaucrat(void) {
}

std::ostream&	operator<<(std::ostream& out, Bureaucrat const& obj) {
	out << HONEY << "Bureaucrat " << obj.getName() << YELLOW << " (Grade " << obj.getGrade() << ")" << RESET << std::endl;
	return out;
}
