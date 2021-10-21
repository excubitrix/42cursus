#ifndef SUPERMUTANT_H
# define SUPERMUTANT_H

# include <iostream>
# include "Enemy.hpp"

class	SuperMutant : public Enemy {

	public:

		SuperMutant(void);
		SuperMutant(SuperMutant const& src);
		virtual ~SuperMutant(void);

		SuperMutant&	operator=(SuperMutant const& src);

		void	takeDamage(int amount);
};

#endif
