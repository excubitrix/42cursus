#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

# include <iostream>

# define RESET "\033[0m"
# define RED "\033[31;1m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define HONEY "\e[38;5;214;1m"
# define PUKE_GREEN "\e[38;5;70;1m"

class	Form;

class	Bureaucrat {

	public:

		Bureaucrat(std::string const name, int grade);
		Bureaucrat(Bureaucrat const& src);
		virtual ~Bureaucrat(void);

		Bureaucrat&	operator=(Bureaucrat const& src);

		class GradeTooHighException : public std::exception {
			virtual const char*	what() const throw();
		};

		class GradeTooLowException : public std::exception {
			virtual const char*	what() const throw();
		};

		std::string const	getName(void) const;
		int					getGrade(void) const;

		void				incrementGrade(void);
		void				decrementGrade(void);

		void				signForm(Form& form);
		void				executeForm(Form const& form);

	private:

		std::string const	_name;
		int					_grade;

		Bureaucrat(void);
};

std::ostream&	operator<<(std::ostream& out, Bureaucrat const& obj);

#endif
