#include "Squad.hpp"
#include "TacticalMarine.hpp"
#include "AssaultTerminator.hpp"

int 	main(void)
{
	ISpaceMarine* bob = new TacticalMarine;
	ISpaceMarine* jim = new AssaultTerminator;
	
	ISquad* vlc = new Squad;
	vlc->push(bob);
	vlc->push(jim);
	for (int i = 0; i < vlc->getCount(); ++i)
	{
		ISpaceMarine* cur = vlc->getUnit(i);
		cur->battleCry();
		cur->rangedAttack();
		cur->meleeAttack();
	}
	delete vlc;

	ISpaceMarine* dave = new TacticalMarine;
	ISpaceMarine* joe = new AssaultTerminator;

	Squad sqd;
	sqd.push(dave);
	sqd.push(joe);
	Squad cpy = sqd;
	for (int i = 0; i < cpy.getCount(); ++i)
	{
		ISpaceMarine* cur = cpy.getUnit(i);
		cur->battleCry();
		cur->rangedAttack();
		cur->meleeAttack();
	}
	sqd = cpy;
	std::cout << "~END~" << std::endl;

	return 0;
}
