#ifndef POWERFIST_H
# define POWERFIST_H

# include "AWeapon.hpp"

class	PowerFist : public AWeapon {

	public:

		PowerFist(void);
		PowerFist(PowerFist const& src);
		virtual ~PowerFist(void);

		PowerFist&	operator=(PowerFist const& src);

		void	attack(void) const;
};

#endif
