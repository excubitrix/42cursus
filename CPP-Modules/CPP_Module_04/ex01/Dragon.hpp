#ifndef DRAGON_H
# define DRAGON_H

# include <iostream>
# include "Enemy.hpp"

class	Dragon : public Enemy {

	public:

		Dragon(void);
		Dragon(Dragon const& src);
		virtual ~Dragon(void);

		Dragon&	operator=(Dragon const& src);

		void	takeDamage(int amount);
};

#endif
