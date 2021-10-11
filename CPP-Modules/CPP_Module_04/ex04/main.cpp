#include "DeepCoreMiner.hpp"
#include "StripMiner.hpp"
#include "Asteroid.hpp"
#include "Comet.hpp"
#include "MiningBarge.hpp"

int		main(void)
{
	MiningBarge* barge = new MiningBarge();

	DeepCoreMiner* deep1 = new DeepCoreMiner();
	DeepCoreMiner* deep2 = new DeepCoreMiner();
	StripMiner* strip1 = new StripMiner();
	StripMiner* strip2 = new StripMiner();
	StripMiner* strip3 = new StripMiner();

	barge->equip(deep1);
	barge->equip(deep2);
	barge->equip(strip1);
	barge->equip(strip2);
	barge->equip(strip3);

	IAsteroid* asteroid = new Asteroid();
	IAsteroid* comet = new Comet();

	barge->mine(asteroid);
	barge->mine(comet);
	
	delete comet;
	delete asteroid;
	delete strip3;
	delete strip2;
	delete strip1;
	delete deep2;
	delete deep1;
	delete barge;
	
	return 0;
}
