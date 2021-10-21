#ifndef ASTEROID_H
# define ASTEROID_H

# include <iostream>
# include "IAsteroid.hpp"
# include "DeepCoreMiner.hpp"
# include "StripMiner.hpp"

class	Asteroid : public IAsteroid {

	public:

		Asteroid(void);
		Asteroid(Asteroid const& src);
		virtual ~Asteroid(void);

		Asteroid&	operator=(Asteroid const& src);

		std::string	beMined(DeepCoreMiner *) const;
		std::string	beMined(StripMiner *) const;
		std::string	getName(void) const;

	private:

		std::string	_name;
};

#endif
