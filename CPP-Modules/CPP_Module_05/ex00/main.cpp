#include "Bureaucrat.hpp"

void	climb(Bureaucrat& bob)
{
	for (int i = 0; i < 10; i++)
	{
		bob.incrementGrade();
		std::cout << bob;
	}
}

void	fall(Bureaucrat& bob)
{
	for (int i = 0; i < 10; i++)
	{
		bob.decrementGrade();
		std::cout << bob;
	}
}

int		main(void)
{
	try
	{
		Bureaucrat bob("Bob", 4);
		std::cout << bob;
		Bureaucrat jim("Jim", -4);
		std::cout << jim;
		Bureaucrat joe("Joe", 154);
		std::cout << joe;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat bob("Bob", 4);
		std::cout << bob;
		Bureaucrat joe("Joe", 154);
		std::cout << joe;
		Bureaucrat jim("Jim", -4);
		std::cout << jim;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat bob("Bob", 4);
		climb(bob);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat jim("Jim", 147);
		fall(jim);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
