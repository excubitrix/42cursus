#ifndef TACTICALMARINE_H
# define TACTICALMARINE_H

# include <iostream>
# include "ISpaceMarine.hpp"

class	TacticalMarine : public ISpaceMarine {

	public:

		TacticalMarine(void);
		TacticalMarine(TacticalMarine const& src);
		virtual ~TacticalMarine(void);

		TacticalMarine&	operator=(TacticalMarine const& src);

		ISpaceMarine*	clone(void) const;
		
		void	battleCry(void) const;
		void	rangedAttack(void) const;
		void	meleeAttack(void) const;
};

#endif
