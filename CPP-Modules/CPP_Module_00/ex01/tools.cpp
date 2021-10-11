#include "tools.hpp"

void	put_welcome_msg(void)
{
	std::cout << "~ " CYAN "DIRECTORY LITE" RESET << std::endl
			  << "~ Welcome to the lite version of " BLUE
			  << "DIRECTORY" RESET "!" << std::endl;
}

void	put_else_msg(void)
{
	std::cout << "~ Supported commands are: " YELLOW "ADD" RESET ", " YELLOW
			  << "SEARCH" RESET " and " YELLOW "EXIT" RESET "." << std::endl
			  << "~ Want more functionality? Upgrade to " << MAGENTA "DIRECTORY PRO"
			  << RESET " now and get 30% OFF our annual plan!" << std::endl;
}

void	put_goodbye_msg(void)
{
	std::cout << "~ Thank you for using " BLUE "DIRECTORY" RESET
			  << " to keep your contacts safe!" << std::endl
			  << "~ Bye!" << std::endl;
}

int		put_eof_msg(void)
{
	std::cout << std::endl << "~ " RED "Received EOF. " RESET "Exiting..." << std::endl;
	put_goodbye_msg();
	return 0;
}
