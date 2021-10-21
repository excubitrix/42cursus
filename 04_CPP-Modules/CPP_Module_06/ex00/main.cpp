#include "Converter.hpp"

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: bad arguments" << std::endl;
		return 1;
	}
	else
	{
		try
		{
			Converter conv(argv[1]);
			std::cout << conv;
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
			return 1;
		}
	}
	return 0;
}
