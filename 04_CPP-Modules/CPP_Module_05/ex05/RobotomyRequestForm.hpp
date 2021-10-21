#ifndef ROBOTOMYREQUESTFORM_H
# define ROBOTOMYREQUESTFORM_H

# include <iostream>
# include "Form.hpp"

class	RobotomyRequestForm : public Form {

	public:

		RobotomyRequestForm(void);
		RobotomyRequestForm(std::string target);
		RobotomyRequestForm(RobotomyRequestForm const& src);
		virtual ~RobotomyRequestForm(void);

		RobotomyRequestForm&	operator=(RobotomyRequestForm const& src);

		std::string	getTarget(void) const;
		
		void	action(void) const;

	private:

		std::string	_target;
};

#endif
