#ifndef ZOMBIEHORDE_H
# define ZOMBIEHORDE_H

# include "Zombie.hpp"

class	ZombieHorde {

	public:

		ZombieHorde(int N);
		~ZombieHorde(void);

		void	announce(void) const;

	private:

		std::string	const _gen_random(const int len) const;

		int			_size;
		Zombie*		_horde;
};

#endif
