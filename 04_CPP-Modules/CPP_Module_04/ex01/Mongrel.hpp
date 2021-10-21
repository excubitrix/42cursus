#ifndef MONGREL_H
# define MONGREL_H

# include <iostream>
# include "Enemy.hpp"

class	Mongrel : public Enemy {

	public:

		Mongrel(void);
		Mongrel(Mongrel const& src);
		virtual ~Mongrel(void);

		Mongrel&	operator=(Mongrel const& src);
};

#endif
