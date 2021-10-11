#include "Directory.hpp"
#include "tools.hpp"

int	main(void)
{
	Directory	directory;
	std::string	command;

	put_welcome_msg();
	put_else_msg();
	while (1)
	{
		std::cout << "~ Please enter a command: ";
		if (!std::getline(std::cin, command))
			return put_eof_msg();
		else if (command == "ADD" && !directory.add_contact())
			return put_eof_msg();
		else if (command == "SEARCH" && !directory.search_contact())
			return put_eof_msg();
		else if (command == "EXIT")
		{
			put_goodbye_msg();
			break ;
		}
		else if (command != "ADD" && command != "SEARCH" && command != "EXIT")
			put_else_msg();
	}
	return 0;
}
