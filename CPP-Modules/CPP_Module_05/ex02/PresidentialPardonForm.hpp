#ifndef PRESIDENTIALPARDONFORM_H
# define PRESIDENTIALPARDONFORM_H

# include <iostream>
# include "Form.hpp"

class	PresidentialPardonForm : public Form {

	public:

		PresidentialPardonForm(void);
		PresidentialPardonForm(std::string target);
		PresidentialPardonForm(PresidentialPardonForm const& src);
		virtual ~PresidentialPardonForm(void);

		PresidentialPardonForm&	operator=(PresidentialPardonForm const& src);

		std::string	getTarget(void) const;

		void	action(void) const;

	private:

		std::string	_target;
};

#endif
