#include "Bureaucrat.hpp"
#include "Form.hpp"

int		main(void)
{

	try
	{
		Form		one("One", 3, 0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Form		one("One", 151, 3);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat	bob("Bob", 4);
		Form		one("One", 3, 1);
		Form		two("Two", 135, 2);
		Form		three("Three", 57, 3);

		std::cout << bob << one << two << three;

		bob.signForm(one);
		bob.signForm(two);
		bob.signForm(three);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat	bob("Bob", 3);
		Form		one("One", 3, 1);
		Form		two("Two", 135, 2);
		Form		three("Three", 57, 3);

		std::cout << bob;

		bob.signForm(one);
		bob.signForm(two);
		bob.signForm(three);
		bob.signForm(three);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
