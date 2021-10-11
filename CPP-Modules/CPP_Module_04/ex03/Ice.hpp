#ifndef ICE_H
# define ICE_H

# include <iostream>
# include "AMateria.hpp"
# include "ICharacter.hpp"

class	Ice : public AMateria {

	public:

		Ice(void);
		Ice(Ice const& src);
		virtual ~Ice(void);

		Ice&	operator=(Ice const& src);

		Ice*	clone(void) const;
};

#endif
