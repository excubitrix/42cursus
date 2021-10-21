#include "Character.hpp"
#include "SuperMutant.hpp"
#include "RadScorpion.hpp"
#include "Mongrel.hpp"
#include "Dragon.hpp"
#include "PlasmaRifle.hpp"
#include "PowerFist.hpp"
#include "Whip.hpp"
#include "RocketLauncher.hpp"

int 	main(void)
{
	Character* me = new Character("me");

	std::cout << *me;
	
	Enemy* a = new SuperMutant();
	Enemy* b = new RadScorpion();
	Enemy* c = new Mongrel();
	Enemy* d = new Dragon();
	
	AWeapon* pr = new PlasmaRifle();
	AWeapon* pf = new PowerFist();
	AWeapon* w = new Whip();
	AWeapon* rl = new RocketLauncher();
	
	me->equip(pr);
	std::cout << *me;
	me->equip(pf);
	
	me->attack(b);
	std::cout << *me;
	me->equip(pr);
	std::cout << *me;
	me->attack(b);
	std::cout << *me;
	me->attack(b);
	std::cout << *me;

	me->attack(a);
	me->attack(a);
	me->attack(a);
	std::cout << *me;
	me->attack(a);
	me->equip(w);
	
	std::cout << *me;
	me->recoverAP();
	me->recoverAP();
	me->recoverAP();
	me->recoverAP();
	std::cout << *me;
	me->attack(a);
	me->attack(a);
	me->equip(rl);
	me->attack(a);
	std::cout << *me;
	me->recoverAP();
	me->recoverAP();
	me->recoverAP();
	me->recoverAP();
	std::cout << *me;

	me->attack(c);
	std::cout << *me;
	me->recoverAP();
	me->recoverAP();
	me->recoverAP();
	std::cout << *me;
	me->attack(d);
	me->equip(pf);
	me->attack(d);
	me->attack(d);
	
	delete rl;
	delete w;
	delete pf;
	delete pr;
	delete d;
	delete me;

	std::cout << "~END~" << std::endl;

	return 0;
}
