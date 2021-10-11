#include "OfficeBlock.hpp"

OfficeBlock::OfficeBlock(void) : _intern(NULL) {
	_bureaucrat[0] = NULL;
	_bureaucrat[1] = NULL;
}

OfficeBlock::OfficeBlock(Intern& intern, Bureaucrat& first, Bureaucrat& second) : _intern(&intern) {
	_bureaucrat[0] = &first;
	_bureaucrat[1] = &second;
}

OfficeBlock::~OfficeBlock(void) {
}

const char*	OfficeBlock::AlreadyExecutorException::what() const throw() {
	return RED "Already assigned to the executor position" RESET;
}

const char*	OfficeBlock::AlreadySignerException::what() const throw() {
	return RED "Already assigned to the signer position" RESET;
}

const char*	OfficeBlock::NoInternException::what() const throw() {
	return RED "No intern" RESET;
}

const char*	OfficeBlock::NoSignerException::what() const throw() {
	return RED "No signing bureaucrat" RESET;
}

const char*	OfficeBlock::NoExecutorException::what() const throw() {
	return RED "No executing bureaucrat" RESET;
}

void	OfficeBlock::setIntern(Intern& intern) {
	this->_intern = &intern;
}

void	OfficeBlock::setSigner(Bureaucrat& bureaucrat) {
	if (&bureaucrat == this->_bureaucrat[1])
		throw AlreadyExecutorException();
	this->_bureaucrat[0] = &bureaucrat;
}

void	OfficeBlock::setExecutor(Bureaucrat& bureaucrat) {
	if (&bureaucrat == this->_bureaucrat[0])
		throw AlreadySignerException();
	this->_bureaucrat[1] = &bureaucrat;
}

void	OfficeBlock::doBureaucracy(std::string const& formName, std::string const& targetName) {
	if (!this->_intern)
		throw NoInternException();
	if (!this->_bureaucrat[0])
		throw NoSignerException();
	if (!this->_bureaucrat[1])
		throw NoExecutorException();
	Form* form = this->_intern->makeForm(formName, targetName);
	this->_bureaucrat[0]->signForm(*form);
	this->_bureaucrat[1]->executeForm(*form);
	delete form;
}
