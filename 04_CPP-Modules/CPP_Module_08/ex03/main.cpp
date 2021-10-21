#include "MindOpen.hpp"

int		main(int argc, char **argv)
{
	if (argc != 2)
		std::cout << "Error: bad arguments" << std::endl;
	else
	{
		try
		{
			MindOpen mo(argv[1]);
			mo.execute();
		}
		catch(const MindOpen::KillException& e)
		{
			
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return 0;
}
