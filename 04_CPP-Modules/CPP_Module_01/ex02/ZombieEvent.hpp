#ifndef ZOMBIEEVENT_H
# define ZOMBIEEVENT_H

# include <iostream>
# include "Zombie.hpp"

class	ZombieEvent {

	public:

		ZombieEvent(void);
		~ZombieEvent(void);

		void	setZombieType(std::string type);
		Zombie*	newZombie(std::string name);

	private:

		static std::string	_type;
};

std::string	gen_random(const int len);
Zombie*		randomChump(void);

#endif
