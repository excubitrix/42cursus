# include <iostream>
# include <iomanip>
# include <fstream>

# define SUCCESS 0
# define FAILURE 1

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31m"

int		main(int argc, char **argv)
{
	if (argc == 1)
	{
		char c;
		while (std::cin.get(c))
			std::cout << c;
		return SUCCESS;
	}
	for (int i = 1; i < argc; i++)
	{
		std::ifstream in;
		in.open(argv[i]);
		if (!in.good())
		{
			std::cout << BOLD RED "Error: " RESET "Failed to open \'" << argv[i] << "\'. " << std::endl
					  << "Verify that the file exists and that you have the right permissions." << std::endl;
			return FAILURE;
		}
		std::cout << in.rdbuf();
		in.close();
	}
	return SUCCESS;
}
