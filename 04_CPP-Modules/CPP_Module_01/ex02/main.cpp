#include "ZombieEvent.hpp"

int		main(void)
{
	ZombieEvent	event;
	Zombie*		horde[10];
	Zombie*		abnormal[4];
	Zombie*		random[4];

	srand(time(NULL));

	event.setZombieType("generic");
	for (int i = 0; i < 10; i++)
	{
		if (!i)
			horde[i] = event.newZombie("Snowball");
		else
			horde[i] = event.newZombie("Snowball " + std::to_string(i + 1));
		horde[i]->announce();
	}

	event.setZombieType("abnormal");
	for (int i = 0; i < 4; i++)
	{
		abnormal[i] = event.newZombie(gen_random(12));
		abnormal[i]->announce();
	}

	for (int i = 0; i < 4; i++)
		random[i] = randomChump();

	for (int i = 3; i >= 0; i--)
		delete random[i];
	for (int i = 3; i >= 0; i--)
		delete abnormal[i];
	for (int i = 9; i >= 0; i--)
		delete horde[i];

	return 0;
}
