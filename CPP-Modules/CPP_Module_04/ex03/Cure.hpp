#ifndef CURE_H
# define CURE_H

# include <iostream>
# include "AMateria.hpp"
# include "ICharacter.hpp"

class	Cure : public AMateria {

	public:

		Cure(void);
		Cure(Cure const& src);
		virtual ~Cure(void);

		Cure&	operator=(Cure const& src);

		Cure*	clone(void) const;
};

#endif
