#include "replace.hpp"

std::string	replace(std::string str, std::string const& s1, std::string const& s2)
{
	size_t	pos = 0;
	while ((pos = str.find(s1, pos)) != std::string::npos)
	{
		str.replace(pos, s1.length(), s2);
		pos += s2.length();
	}
	return str;
}

int		main(int argc, char **argv)
{
	if (argc != 4 || !argv[2] || !argv[3])
	{
		std::cout << RED "Error: Wrong number of arguments." RESET << std::endl;
		return FAILURE;
	}
	
	std::ifstream in(argv[1]);
	if (!in.good())
	{
		std::cout << RED "Error: Failed to open the file. " RESET
				  << "Verify that the file exists and that you have the right permissions."
				  << std::endl;
		return FAILURE;
	}

	std::ofstream out(argv[1] + std::string(".replace"));
	if (!out.good())
	{
		std::cout << RED "Error: ofstream.open() failed." RESET << std::endl;
		return FAILURE;
	}

	std::ostringstream ss;
	ss << in.rdbuf();

	out << replace(ss.str(), argv[2], argv[3]);

	in.close();
	out.close();

	return SUCCESS;
}
