#ifndef ASSAULTTERMINATOR_H
# define ASSAULTTERMINATOR_H

# include <iostream>
# include "ISpaceMarine.hpp"

class	AssaultTerminator : public ISpaceMarine {

	public:

		AssaultTerminator(void);
		AssaultTerminator(AssaultTerminator const& src);
		virtual ~AssaultTerminator(void);

		AssaultTerminator&	operator=(AssaultTerminator const& src);

		ISpaceMarine*	clone(void) const;
		
		void	battleCry(void) const;
		void	rangedAttack(void) const;
		void	meleeAttack(void) const;
};

#endif
