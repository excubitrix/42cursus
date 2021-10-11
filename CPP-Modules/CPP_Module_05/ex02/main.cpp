#include <iostream>
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int		main(void)
{
	srand(time(NULL));

	try
	{
		Bureaucrat	alice("Alice", 56);

		std::cout << alice;

		ShrubberyCreationForm	shrub("school");
		RobotomyRequestForm		robot("Snowball");
		PresidentialPardonForm	pres("Jack");

		std::cout << shrub << robot << pres;

		alice.signForm(shrub);
		alice.signForm(robot);
		alice.signForm(pres);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat	alice("Alice", 56);
		Bureaucrat	jane("Jane", 21);

		std::cout << alice << jane;

		ShrubberyCreationForm	shrub("school");

		std::cout << shrub;

		alice.signForm(shrub);
		jane.signForm(shrub);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat	margot("Margot", 3);

		std::cout << margot;

		ShrubberyCreationForm	shrub("school");

		std::cout << shrub;

		margot.executeForm(shrub);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat	alice("Alice", 56);
		Bureaucrat	jane("Jane", 21);

		std::cout << alice << jane;

		ShrubberyCreationForm	shrub("school");
		RobotomyRequestForm		robot("Snowball");
		PresidentialPardonForm	pres("Jack");

		std::cout << shrub << robot << pres;

		jane.signForm(shrub);
		jane.signForm(robot);
		jane.signForm(pres);

		alice.executeForm(shrub);
		alice.executeForm(robot);
		alice.executeForm(pres);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat	jane("Jane", 21);

		std::cout << jane;

		ShrubberyCreationForm	shrub("school");
		RobotomyRequestForm		robot("Snowball");
		PresidentialPardonForm	pres("Jack");

		std::cout << shrub << robot << pres;

		jane.signForm(shrub);
		jane.signForm(robot);
		jane.signForm(pres);

		jane.executeForm(shrub);
		jane.executeForm(robot);
		jane.executeForm(pres);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat	jane("Jane", 21);
		Bureaucrat	margot("Margot", 3);

		std::cout << jane << margot;

		ShrubberyCreationForm	shrub("school");
		RobotomyRequestForm		robot("Snowball");
		PresidentialPardonForm	pres("Jack");

		std::cout << shrub << robot << pres;

		jane.signForm(shrub);
		jane.signForm(robot);
		jane.signForm(pres);

		margot.executeForm(shrub);
		margot.executeForm(robot);
		margot.executeForm(pres);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
