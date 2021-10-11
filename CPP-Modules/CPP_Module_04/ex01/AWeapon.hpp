#ifndef AWEAPON_H
# define AWEAPON_H

# include <iostream>

class	AWeapon {

	public:

		AWeapon(std::string const& name, int apcost, int damage);
		AWeapon(AWeapon const& src);
		virtual ~AWeapon(void);

		AWeapon&	operator=(AWeapon const& src);

		std::string	getName(void) const;

		int		getAPCost(void) const;
		int		getDamage(void) const;

		virtual void	attack(void) const = 0;

	protected:

		std::string	_name;

		int		_apcost;
		int		_damage;

	private:

		AWeapon(void);
};

#endif
