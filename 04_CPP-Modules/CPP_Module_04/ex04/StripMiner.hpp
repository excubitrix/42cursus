#ifndef STRIPMINER_H
# define STRIPMINER_H

# include "IMiningLaser.hpp"
# include "IAsteroid.hpp"

class	StripMiner : public IMiningLaser {

	public:

		StripMiner(void);
		StripMiner(StripMiner const& src);
		virtual ~StripMiner(void);

		StripMiner&	operator=(StripMiner const& src);

		void	mine(IAsteroid* target);
};

#endif
