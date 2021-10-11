#ifndef MUTANTPIGTERMINATIONFORM_H
# define MUTANTPIGTERMINATIONFORM_H

# include <iostream>
# include "Form.hpp"

class	MutantPigTerminationForm : public Form {

	public:

		MutantPigTerminationForm(void);
		MutantPigTerminationForm(std::string target);
		MutantPigTerminationForm(MutantPigTerminationForm const& src);
		virtual ~MutantPigTerminationForm(void);

		MutantPigTerminationForm&	operator=(MutantPigTerminationForm const& src);

		std::string	getTarget(void) const;
		
		void	action(void) const;

	private:

		std::string	_target;
};

#endif
