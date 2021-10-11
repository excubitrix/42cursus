#ifndef Intern_H
# define Intern_H

# include <iostream>
# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"

class	Intern {

	public:

		typedef		Form*(Intern::*functionPtr)(std::string const& target);

		Intern(void);
		Intern(Intern const& src);
		virtual ~Intern(void);

		Intern&	operator=(Intern const& src);

		class UnknownFormException : public std::exception {
			virtual const char*	what() const throw();
		};

		Form*	createShrubberyCreationForm(std::string const& target);
		Form*	createRobotomyRequestForm(std::string const& target);
		Form*	createPresidentialPardonForm(std::string const& target);

		Form*	makeForm(std::string const& name, std::string const& target);

	private:

		static std::string const	_formName[6];
		static functionPtr const	_form[6];
};

#endif
