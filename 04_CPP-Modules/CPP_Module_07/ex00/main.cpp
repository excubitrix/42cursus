#include <iostream>
#include "whatever.hpp"

#define RESET "\033[0m"
#define YELLOW "\033[33m"

int		main(void)
{
	std::cout << YELLOW << "CHAR" << RESET << std::endl;
	{
		char a = 'A';
		char b = 'B';

		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "*swap*" << std::endl;
		::swap(a, b);
		std::cout << "a = " << a << ", b = " << b << std::endl;

		std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
		std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
	}
	std::cout << YELLOW << "INT" << RESET << std::endl;
	{
		int	a = 19;
		int	b = 42;

		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "*swap*" << std::endl;
		::swap(a, b);
		std::cout << "a = " << a << ", b = " << b << std::endl;

		std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
		std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
	}
	std::cout << YELLOW << "FLOAT" << RESET << std::endl;
	{
		float a = 42.0f;
		float b = 19.0f;

		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "*swap*" << std::endl;
		::swap(a, b);
		std::cout << "a = " << a << ", b = " << b << std::endl;

		std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
		std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
	}
	std::cout << YELLOW << "DOUBLE" << RESET << std::endl;
	{
		double a = -19.0;
		double b = -42.0;

		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "*swap*" << std::endl;
		::swap(a, b);
		std::cout << "a = " << a << ", b = " << b << std::endl;

		std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
		std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
	}
	std::cout << YELLOW << "STRING" << RESET << std::endl;
	{
		std::string a = "hello";
		std::string b = "world";

		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "*swap*" << std::endl;
		::swap(a, b);
		std::cout << "a = " << a << ", b = " << b << std::endl;

		std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
		std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
	}
	return 0;
}
