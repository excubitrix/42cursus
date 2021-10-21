#ifndef AMATERIA_H
# define AMATERIA_H

# include <iostream>
# include "ICharacter.hpp"

class	AMateria {

	public:

		AMateria(std::string const& type);
		AMateria(AMateria const& src);
		virtual ~AMateria(void);

		AMateria&	operator=(AMateria const& src);

		std::string const&	getType(void) const;
		unsigned int		getXP(void) const;

		virtual AMateria*	clone(void) const = 0;
		virtual void		use(ICharacter& target);
	
	protected:

		std::string		_type;
		unsigned int	_xp;

	private:

		AMateria(void);
};

#endif
