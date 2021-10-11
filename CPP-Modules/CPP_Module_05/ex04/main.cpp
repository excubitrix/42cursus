#include <iostream>
#include "OfficeBlock.hpp"

int		main(void)
{
	srand(time(NULL));

	Intern idiotOne;
	Bureaucrat hermes = Bureaucrat("Hermes Conrad", 37);
	Bureaucrat bob = Bureaucrat("Bobby Bobson", 123);
	OfficeBlock ob;

	ob.setIntern(idiotOne);
	ob.setSigner(bob);
	ob.setExecutor(hermes);
	
	try
	{
		ob.doBureaucracy("mutant pig termination", "Pigley");
		ob.setSigner(hermes);
	}
	catch (OfficeBlock::AlreadyExecutorException & e)
	{
		std::cerr << RED << "This bureaucrat has already been assigned to the executor position." << RESET << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Intern		intern = Intern();
		Bureaucrat	signing("Robert", 21);
		Bureaucrat	executing("Nancy", 3);

		std::cout << signing << executing;
		
		OfficeBlock office(intern, signing, executing);

		office.doBureaucracy("shrubbery creation", "school");
		office.doBureaucracy("robotomy request", "Snowball");
		office.doBureaucracy("presidential pardon", "Jack");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
