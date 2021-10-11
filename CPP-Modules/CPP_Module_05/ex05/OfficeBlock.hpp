#ifndef OFFICBLOCK_H
# define OFFICBLOCK_H

# include <iostream>
# include "Bureaucrat.hpp"
# include "Intern.hpp"

class	OfficeBlock {

	public:

		OfficeBlock(void);
		OfficeBlock(Intern& intern, Bureaucrat& first, Bureaucrat& second);
		OfficeBlock(OfficeBlock const& src);
		virtual ~OfficeBlock(void);

		OfficeBlock&	operator=(OfficeBlock const& src);

		class AlreadyExecutorException : public std::exception {
			virtual const char*	what() const throw();
		};

		class AlreadySignerException : public std::exception {
			virtual const char*	what() const throw();
		};

		class NoInternException : public std::exception {
			virtual const char*	what() const throw();
		};

		class NoSignerException : public std::exception {
			virtual const char*	what() const throw();
		};

		class NoExecutorException : public std::exception {
			virtual const char*	what() const throw();
		};

		void	setIntern(Intern& intern);
		void	setSigner(Bureaucrat& bureaucrat);
		void	setExecutor(Bureaucrat& bureaucrat);

		Intern*		getIntern(void);
		Bureaucrat*	getSigner(void);
		Bureaucrat*	getExecutor(void);

		void	doBureaucracy(std::string const& formName, std::string const& targetName);

	private:

		Intern*		_intern;
		Bureaucrat*	_bureaucrat[2];
};

#endif
