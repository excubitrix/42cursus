#ifndef Intern_H
# define Intern_H

# include <iostream>
# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"
# include "MutantPigTerminationForm.hpp"

# define N 8

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
		Form*	createMutantPigTerminationForm(std::string const& target);

		Form*	makeForm(std::string const& name, std::string const& target);

	private:

		static std::string const	_formName[N];
		static functionPtr const	_form[N];
};

#endif
