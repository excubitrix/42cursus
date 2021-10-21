#ifndef SHRUBBERYCREATIONFORM_H
# define SHRUBBERYCREATIONFORM_H

# include <iostream>
# include <fstream>
# include "Form.hpp"

class	ShrubberyCreationForm : public Form {

	public:

		ShrubberyCreationForm(void);
		ShrubberyCreationForm(std::string target);
		ShrubberyCreationForm(ShrubberyCreationForm const& src);
		virtual ~ShrubberyCreationForm(void);

		ShrubberyCreationForm&	operator=(ShrubberyCreationForm const& src);

		class OpenException: public std::exception {
			virtual const char* what() const throw();
		};

		class WriteException: public std::exception {
			virtual const char* what() const throw();
		};

		std::string	getTarget(void) const;

		void	action(void) const;

	private:

		static std::string	_shrub[3];
		std::string			_target;
};

#endif
