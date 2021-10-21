#include "Human.hpp"

int		main(void)
{
	Human	bob;

	bob.action("melee", "zombie");
	bob.action("ranged", "zombie");
	bob.action("shout", "zombie");

	return 0;
}
