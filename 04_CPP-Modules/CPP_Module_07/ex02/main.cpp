#include <iostream>
#include "Array.hpp"

#define RESET "\033[0m"
#define YELLOW "\033[33m"

int		main(void)
{
	std::cout << YELLOW << "CHAR" << RESET << std::endl;
	Array<char> charArr1;
	Array<char> charArr2(5);
	charArr1 = charArr2;
	for (size_t i = 0; i < charArr1.size(); i++)
	{
		charArr1[i] = i + 97;
		std::cout << charArr1[i] << " ";
	}
	std::cout << std::endl;
	charArr2 = charArr1;
	for (size_t i = 0; i < charArr2.size(); i++)
		std::cout << charArr2[i] << " ";
	std::cout << std::endl;
	std::cout << YELLOW << "INT" << RESET << std::endl;
	Array<int> intArr1;
	Array<int> intArr2(5);
	intArr1 = intArr2;
	for (size_t i = 0; i < intArr1.size(); i++)
	{
		intArr1[i] = i;
		std::cout << intArr1[i] << " ";
	}
	std::cout << std::endl;
	intArr2 = intArr1;
	for (size_t i = 0; i < intArr2.size(); i++)
		std::cout << intArr2[i] << " ";
	std::cout << std::endl;
	std::cout << YELLOW << "FLOAT" << RESET << std::endl;
	Array<float> floatArr1;
	Array<float> floatArr2(5);
	floatArr1 = floatArr2;
	for (size_t i = 0; i < floatArr1.size(); i++)
	{
		floatArr1[i] = i;
		std::cout << floatArr1[i] << " ";
	}
	std::cout << std::endl;
	floatArr2 = floatArr1;
	for (size_t i = 0; i < floatArr2.size(); i++)
		std::cout << floatArr2[i] << " ";
	std::cout << std::endl;
	std::cout << YELLOW << "DOUBLE" << RESET << std::endl;
	Array<double> doubleArr1;
	Array<double> doubleArr2(5);
	doubleArr1 = doubleArr2;
	for (size_t i = 0; i < doubleArr1.size(); i++)
	{
		doubleArr1[i] = i;
		std::cout << doubleArr1[i] << " ";
	}
	std::cout << std::endl;
	doubleArr2 = doubleArr1;
	for (size_t i = 0; i < doubleArr2.size(); i++)
		std::cout << doubleArr2[i] << " ";
	std::cout << std::endl;
	std::cout << YELLOW << "BOOL" << RESET << std::endl;
	Array<bool> boolArr1;
	Array<bool> boolArr2(2);
	boolArr1 = boolArr2;
	boolArr1[0] = false;
	boolArr1[1] = true;
	for (size_t i = 0; i < boolArr1.size(); i++)
		std::cout << boolArr1[i] << " ";
	std::cout << std::endl;
	boolArr2 = boolArr1;
	for (size_t i = 0; i < boolArr2.size(); i++)
		std::cout << boolArr2[i] << " ";
	std::cout << std::endl;
	std::cout << YELLOW << "STRING" << RESET << std::endl;
	Array<std::string> stringArr1;
	Array<std::string> stringArr2(5);
	stringArr1 = stringArr2;
	stringArr1[0] = "templates";
	stringArr1[1] = "are";
	stringArr1[2] = "fun!";
	stringArr1[3] = ":D";
	stringArr1[4] = "";
	for (size_t i = 0; i < stringArr1.size(); i++)
		std::cout << stringArr1[i] << " ";
	std::cout << std::endl;
	stringArr2 = stringArr1;
	for (size_t i = 0; i < stringArr2.size(); i++)
		std::cout << stringArr2[i] << " ";
	std::cout << std::endl;
	std::cout << YELLOW << "EXCEPTIONS" << RESET << std::endl;
	try
	{
		intArr1[-1] = -1;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		intArr1[5] = 5;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
