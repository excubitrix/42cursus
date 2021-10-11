#ifndef COMET_H
# define COMET_H

# include <iostream>
# include "IAsteroid.hpp"
# include "DeepCoreMiner.hpp"
# include "StripMiner.hpp"

class	Comet :  public IAsteroid {

	public:

		Comet(void);
		Comet(Comet const& src);
		virtual ~Comet(void);

		Comet&	operator=(Comet const& src);

		std::string	beMined(DeepCoreMiner *) const;
		std::string	beMined(StripMiner *) const;
		std::string	getName(void) const;

	private:

		std::string	_name;
};

#endif
