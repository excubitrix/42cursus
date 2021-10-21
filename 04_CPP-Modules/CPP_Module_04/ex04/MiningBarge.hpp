#ifndef MININGBARGE_H
# define MININGBARGE_H

# include "IMiningLaser.hpp"
# include "IAsteroid.hpp"

class	MiningBarge {

	public:

		MiningBarge(void);
		MiningBarge(MiningBarge const& src);
		virtual ~MiningBarge(void);

		MiningBarge&	operator=(MiningBarge const& src);

		void	equip(IMiningLaser* laser);
		void	mine(IAsteroid* target) const;
	
	private:

		IMiningLaser*	_laser[4];
};

#endif
