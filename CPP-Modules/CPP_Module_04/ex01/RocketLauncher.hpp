#ifndef ROCKETLAUNCHER_H
# define ROCKETLAUNCHER_H

# include "AWeapon.hpp"

class	RocketLauncher : public AWeapon {

	public:

		RocketLauncher(void);
		RocketLauncher(RocketLauncher const& src);
		virtual ~RocketLauncher(void);

		RocketLauncher&	operator=(RocketLauncher const& src);

		void	attack(void) const;
};

#endif
