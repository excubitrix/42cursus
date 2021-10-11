#include "Sorcerer.hpp"
#include "Victim.hpp"
#include "Peon.hpp"
#include "Boy.hpp"
#include "Princess.hpp"

int	main(void)
{
	Sorcerer robert("Robert", "the Magnificent");

	Victim jim("Jimmy");
	Peon joe("Joe");
	Boy pinocchio1("Pinocchio1");
	Boy pinocchio2("Pinocchio2");
	Princess emma1("Emma1");
	Princess emma2("Emma2");

	std::cout << robert << jim << joe << pinocchio1 << pinocchio2 << emma1 << emma2;

	robert.polymorph(jim);
	robert.polymorph(joe);
	robert.polymorph(pinocchio1);
	pinocchio2.getPolymorphed();
	robert.polymorph(emma1);
	emma2.getPolymorphed();
	
	std::cout << "~END~" << std::endl;
	
	return 0;
}
