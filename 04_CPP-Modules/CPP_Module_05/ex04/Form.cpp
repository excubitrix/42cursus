#include "Form.hpp"

Form::Form(std::string const name, int signGrade, int execGrade) : _name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade) {
	if (this->_signGrade < 1 || this->_execGrade < 1)
		throw Form::GradeTooHighException();
	if (this->_signGrade > 150 || this->_execGrade > 150)
		throw Form::GradeTooLowException();
}

Form::Form(Form const& src) : _name(src._name), _signed(src._signed), _signGrade(src._signGrade), _execGrade(src._execGrade) {
	if (this->_signGrade < 1 || this->_execGrade < 1)
		throw Form::GradeTooHighException();
	if (this->_signGrade > 150 || this->_execGrade > 150)
		throw Form::GradeTooLowException();
}

Form::~Form(void) {
}

Form&	Form::operator=(Form const& src) {
	if (this != &src)
		this->_signed = src._signed;
	return *this;
}

const char*	Form::GradeTooHighException::what() const throw() {
	return RED "Grade too high" RESET;
}

const char*	Form::GradeTooLowException::what() const throw() {
	return RED "Grade too low" RESET;
}

const char*	Form::AlreadySignedException::what() const throw() {
	return RED "Already signed" RESET;
}

const char*	Form::NotSignedException::what() const throw() {
	return RED "Not signed" RESET;
}

std::string const	Form::getName(void) const {
	return this->_name;
}

bool	Form::getStatus(void) const {
	return this->_signed;
}

int Form::getSignGrade(void) const {
	return this->_signGrade;
}

int Form::getExecGrade(void) const {
	return this->_execGrade;
}

void	Form::beSigned(Bureaucrat const& signee) {
	if (signee.getGrade() > this->getSignGrade())
		throw Form::GradeTooLowException();
	else if (this->_signed)
		throw Form::AlreadySignedException();
	this->_signed = true;
}

void	Form::execute(Bureaucrat const& executor) const {
	if (executor.getGrade() > this->getExecGrade())
		throw Form::GradeTooLowException();
	else if (!this->_signed)
		throw Form::NotSignedException();
	this->action();
}

std::ostream&	operator<<(std::ostream& out, Form const& obj) {
	out << CYAN << obj.getName() << " Form " << YELLOW << "(s.grade " << obj.getSignGrade()
		<< ", ex.grade " << obj.getExecGrade() << ")" << RESET << std::endl;
	return out;
}
