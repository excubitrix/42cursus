#include <iostream>
#include "CentralBureaucracy.hpp"

std::string const	genRandom(const int len) {
	std::string tmp;
    std::string const alpha = "abcdefghijklmnopqrstuvwxyz";

	tmp.reserve(len);

	for (int i = 0; i < len; ++i)
		tmp += alpha[rand() % alpha.length()];
	tmp[0] = std::toupper(tmp[0]);

	return tmp;
}

int		main(void)
{
	srand(time(NULL));

	CentralBureaucracy	nightmare;
	Bureaucrat*			b[40];

	try
	{
		for (int i = 0; i < 40; i++)
		{
			b[i] = new Bureaucrat(genRandom(6), rand() % 150 + 1);
			nightmare.hire(b[i]);
		}
		for (int i = 0; i < 42; i++)
			nightmare.queueUp(genRandom(6));
		nightmare.doBureaucracy();
	}
	catch (CentralBureaucracy::NoSeatsLeftException & e)
	{
		for (int i = 0; i < 40; i++)
			delete b[i];
		std::cerr << RED << "No positions left to fill." << RESET << std::endl;
	}
	catch(const std::exception& e)
	{
		for (int i = 0; i < 40; i++)
			delete b[i];
		std::cerr << e.what() << std::endl;
	}
	for (int i = 0; i < 40; i++)
		delete b[i];

	return 0;
}
