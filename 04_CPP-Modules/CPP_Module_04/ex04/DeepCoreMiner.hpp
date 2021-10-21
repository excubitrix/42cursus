#ifndef DEEPCOREMINER_H
# define DEEPCOREMINER_H

# include "IMiningLaser.hpp"
# include "IAsteroid.hpp"

class	DeepCoreMiner : public IMiningLaser {

	public:

		DeepCoreMiner(void);
		DeepCoreMiner(DeepCoreMiner const& src);
		virtual ~DeepCoreMiner(void);

		DeepCoreMiner&	operator=(DeepCoreMiner const& src);

		void	mine(IAsteroid* target);
};

#endif
