#include <iostream>
#include <vector>
#include "Span.hpp"

#define RESET "\033[0m"
#define YELLOW "\033[33m"

int 	main(void)
{
	srand(time(NULL));
	std::cout << YELLOW << "FROM SUBJECT" << RESET << std::endl;
	{
		Span sp = Span(5);

		sp.addNumber(5);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
		
		std::cout << YELLOW << "EXCEPTION" << RESET << std::endl;
		try
		{
			sp.addNumber(13);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	std::cout << YELLOW << "TEST WITH 10 NUMBERS" << RESET << std::endl;
	{
		int n = 10;

		Span sp = Span(n);
		std::vector<int> v;

		for (int i = 0; i < n; i++)
			v.push_back(rand() % 100);

		sp.addNumber(v.begin(), v.end());

		std::cout << "Numbers: ";
		sp.printNumbers();

		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: "  << sp.longestSpan() << std::endl;
	}
	std::cout << YELLOW << "TEST WITH 10000 NUMBERS" << RESET << std::endl;
	{
		int n = 10000;

		Span sp = Span(n);
		std::vector<int> v;

		for (int i = 0; i < n; i++)
			v.push_back(rand() % 100000);

		sp.addNumber(v.begin(), v.end());

		std::cout << "Numbers: ";
		sp.printNumbers();

		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	}
	return 0;
}
