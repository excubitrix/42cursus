#include "ShrubberyCreationForm.hpp"

std::string	ShrubberyCreationForm::_shrub[3] = {
	"         #o#\n"
	"   ####o#\n"
	"  #o# \\#|_#,#\n"
	" ###\\ |/   #o#\n"
	"  # {}{      #\n"
	"     }{{\n"
	"    ,'  `\n",

	"    |\n"
	"   \\|/\n"
	"  \\\\|//\n"
	" \\\\\\|///\n"
	" \\\\\\|///\n"
	"  \\\\|//\n"
	"   \\|/\n",

	"     ccee88oo\n"
	"  C8O8O8Q8PoOb o8oo\n"
	" dOB69QO8PdUOpugoO9bD\n"
	"CgggbU8OU qOp qOdoUOdcb\n"
	"    6OuU  /p u gcoUodpP\n"
	"      \\\\//  /douUP\n"
	"        \\\\////\n"
};

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : Form("Shrubbery Creation", 145, 137), _target(target) {
	srand(time(NULL));
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const& src) : Form("Shrubbery Creation", 145, 137), _target(src._target) {
	*this = src;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {
}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=(ShrubberyCreationForm const& src) {
	if (this != &src)
		this->_target = src._target;
	return *this;
}

const char* ShrubberyCreationForm::OpenException::what() const throw() {
	return "Failed to open file";
}

const char* ShrubberyCreationForm::WriteException::what() const throw() {
	return "Write error";
}

std::string	ShrubberyCreationForm::getTarget(void) const {
	return this->_target;
}

void	ShrubberyCreationForm::action(void) const {
	std::ofstream out;
	out.open(this->_target + "_shrubbery", std::ios_base::app);
	if (!out.good())
		throw OpenException();
	out << this->_shrub[rand() % 3] << std::endl;
	if (!out.good())
		throw WriteException();
	out.close();
}
