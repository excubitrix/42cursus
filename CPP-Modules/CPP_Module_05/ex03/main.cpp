#include <iostream>
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"

int		main(void)
{
	srand(time(NULL));

	try
	{
		Intern	intern = Intern();

		Form* shrub;
		Form* robot;
		Form* pres;

		shrub = intern.makeForm("shrubbery creation", "school");
		robot = intern.makeForm("robotomy request", "Snowball");
		pres = intern.makeForm("presidential pardon", "Jack");

		std::cout << *shrub << *robot << *pres;

		delete pres;
		delete robot;
		delete shrub;

		shrub = intern.makeForm("Shrubbery Creation", "school");
		robot = intern.makeForm("Robotomy Request", "Snowball");
		pres = intern.makeForm("Presidential Pardon", "Jack");

		std::cout << *shrub << *robot << *pres;

		delete pres;
		delete robot;
		delete shrub;

		shrub = intern.makeForm("Random", "n/a");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
