#ifndef FORM_H
# define FORM_H

# include <iostream>
# include "Bureaucrat.hpp"

class	Form {

	public:

		Form(void);
		Form(std::string const name, int signGrade, int execGrade);
		Form(Form const& src);
		virtual ~Form(void);

		Form&	operator=(Form const& src);

		class GradeTooHighException : public std::exception {
			virtual const char*	what() const throw();
		};

		class GradeTooLowException : public std::exception {
			virtual const char*	what() const throw();
		};

		class AlreadySignedException : public std::exception {
			virtual const char*	what() const throw();
		};

		std::string const	getName(void) const;
		bool				getStatus(void) const;
		int 				getSignGrade(void) const;
		int 				getExecGrade(void) const;

		void				beSigned(Bureaucrat const& signee);

	private:

		std::string const	_name;
		bool				_signed;
		int const			_signGrade;
		int const			_execGrade;
};

std::ostream&	operator<<(std::ostream& out, Form const& obj);

#endif
