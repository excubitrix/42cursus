#include <iostream>
#include "iter.hpp"

#define RESET "\033[0m"
#define YELLOW "\033[33m"

template<typename T>
void	display(T const &value)
{
	std::cout << value << " ";
}

int		main(void)
{
	std::cout << YELLOW << "CHAR" << RESET << std::endl;
	char charArr[5] = "heho";
	iter(charArr, 5, &display);
	std::cout << std::endl;

	std::cout << YELLOW << "INT" << RESET << std::endl;
	int intArr[5] = { 0, 1, 2, 3, 4 };
	iter(intArr, 5, &display);
	std::cout << std::endl;

	std::cout << YELLOW << "FLOAT" << RESET << std::endl;
	float floatArr[5] = { 0.0f, 1.1f, 2.2f, 3.3f, 4.4f };
	iter(floatArr, 5, &display);
	std::cout << std::endl;

	std::cout << YELLOW << "DOUBLE" << RESET << std::endl;
	double doubleArr[5] = { 0.00, 1.11, 2.22, 3.33, 4.44 };
	iter(doubleArr, 5, &display);
	std::cout << std::endl;

	std::cout << YELLOW << "BOOL" << RESET << std::endl;
	bool boolArr[2] = { false, true };
	iter(boolArr, 2, &display);
	std::cout << std::endl;

	std::cout << YELLOW << "STRING" << RESET << std::endl;
	std::string stringArr[5] = {
		"templates",
		"are",
		"fun!",
		":D",
		""
	};
	iter(stringArr, 5, &display);
	std::cout << std::endl;

	return 0;
}
