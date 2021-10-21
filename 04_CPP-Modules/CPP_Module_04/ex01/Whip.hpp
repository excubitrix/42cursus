#ifndef WHIP_H
# define WHIP_H

# include "AWeapon.hpp"

class	Whip : public AWeapon {

	public:

		Whip(void);
		Whip(Whip const& src);
		virtual ~Whip(void);

		Whip&	operator=(Whip const& src);

		void	attack(void) const;
};

#endif
