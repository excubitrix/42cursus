#ifndef IMININGLASER_H
# define IMININGLASER_H

# include <iostream>

class	IAsteroid;

class	IMiningLaser {

	public:

		virtual ~IMiningLaser() {}
		virtual void mine(IAsteroid*) = 0;
};

#endif
