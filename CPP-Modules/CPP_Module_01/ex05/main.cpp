#include "Human.hpp"

int		main(void)
{
	srand(time(NULL));
	
	Human	bob;
	Human	marley;
	Human	dave;
	Human	cindy;

	std::cout << std::endl << bob.identify() << std::endl;
	std::cout << bob.getBrain().identify() << std::endl << std::endl;

	std::cout << marley.identify() << std::endl;
	std::cout << marley.getBrain().identify() << std::endl << std::endl;

	std::cout << dave.identify() << std::endl;
	std::cout << dave.getBrain().identify() << std::endl << std::endl;

	std::cout << cindy.identify() << std::endl;
	std::cout << cindy.getBrain().identify() << std::endl << std::endl;
}
