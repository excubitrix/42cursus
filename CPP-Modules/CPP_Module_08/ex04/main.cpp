#include "Calculator.hpp"

int 	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: bad arguments" << std::endl;
		return 1;
	}
	try
	{
		Calculator calc(argv[1]);
		calc.displayTokens();
		calc.displayPostfix();
		calc.evaluate();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
