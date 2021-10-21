#ifndef CHARACTER_H
# define CHARACTER_H

# include <iostream>
# include "ICharacter.hpp"
# include "AMateria.hpp"

class	Character : public ICharacter {

	public:

		Character(std::string const& name);
		Character(Character const& src);
		virtual ~Character(void);

		Character&	operator=(Character const& src);

		std::string const&	getName(void) const;

		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);
	
	private:

		std::string	_name;

		AMateria*	_inventory[4];

		Character(void);
};

#endif
