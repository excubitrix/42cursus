#include <iostream>

int	main(int argc, char **argv)
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		int i = 0;
		while (argv[++i])
		{
			int j = 0;
			while (argv[i][j])
				std::cout << (char)std::toupper(argv[i][j++]);
		}
	}
	std::cout << std::endl;
	return 0;
}
