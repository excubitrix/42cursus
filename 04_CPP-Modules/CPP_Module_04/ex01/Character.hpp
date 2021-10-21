#ifndef CHARACTER_H
# define CHARACTER_H

# include <iostream>
# include "AWeapon.hpp"
# include "Enemy.hpp"

class	Character {

	public:

		Character(std::string const& name);
		Character(Character const& src);
		~Character(void);

		Character&	operator=(Character const& src);

		void	recoverAP(void);
		void	equip(AWeapon* weapon);
		void	attack(Enemy* enemy);

		std::string	getName(void) const;
		int			getAP(void) const;
		AWeapon*	getWeapon(void) const;

	private:

		std::string	_name;

		int			_ap;
		AWeapon*	_weapon;

		Character(void);
};

std::ostream&	operator<<(std::ostream& out, Character const& src);

#endif
