#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>

#define RESET "\033[0m"
#define YELLOW "\033[33m"

template <typename T>
void	test_easyfind(T& arr, int n)
{
	try
	{
		std::cout << std::endl
				  << "Searching: " << n << std::endl
				  << "Found: " << *easyfind(arr, n) << std::endl
				  << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}
}

int 	main(void)
{
	std::cout << YELLOW << "EMPTY CONTAINER" << RESET << std::endl;
	{
		std::vector<int>	empty;

		std::cout << "Vector: ";
		for (std::vector<int>::iterator i = empty.begin(); i != empty.end(); ++i)
			std::cout << *i << " ";
		std::cout << std::endl;

		test_easyfind(empty, 0);
	}
	std::cout << YELLOW << "VECTOR" << RESET << std::endl;
	{
		std::vector<int>	vector;

		for (int i = 0; i < 5; i++)
			vector.push_back(i);
		std::cout << "Vector: ";
		for (std::vector<int>::iterator i = vector.begin(); i != vector.end(); ++i)
			std::cout << *i << " ";
		std::cout << std::endl;

		test_easyfind(vector, 4);
	}
	std::cout << YELLOW << "DEQUE" << RESET << std::endl;
	{
		std::deque<int>	deque(5);

		for (int i = 0; i < 5; i++)
			deque[i] = i;
		std::cout << "Deque: ";
		for (std::deque<int>::iterator i = deque.begin(); i != deque.end(); ++i)
			std::cout << *i << " ";
		std::cout << std::endl;

		test_easyfind(deque, 2);
	}
	std::cout << YELLOW << "LIST" << RESET << std::endl;
	{
		std::list<int> list;

		for (int i = 0; i < 5; i++)
			list.push_back(i);
		std::cout << "Set: ";
		for (std::list<int>::iterator i = list.begin(); i != list.end(); ++i)
			std::cout << *i << " ";
		std::cout << std::endl;

		test_easyfind(list, 5);
	}
	std::cout << YELLOW << "SET" << RESET << std::endl;
	{
		std::set<int>	set;

		for (int i = 0; i < 5; i++)
			set.insert(i);
		std::cout << "Set: ";
		for (std::set<int>::iterator i = set.begin(); i != set.end(); ++i)
			std::cout << *i << " ";
		std::cout << std::endl;

		test_easyfind(set, 1);
	}
	return 0;
}
