#include "Calculator.hpp"

bool	isValid(std::string s, int* pos)
{
	while (s[++(*pos)])
		if (!isspace(s[*pos]) && !isdigit(s[*pos]) && s[*pos] != '.'
			&& s[*pos] != '+' && s[*pos] != '-' && s[*pos] != '*' && s[*pos] != '/'
			&& s[*pos] != '(' && s[*pos] != ')')
			return false;
	return true;
}

int 	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: Wrong number of arguments" << std::endl;
		return FAILURE;
	}
	int pos = -1;
	if (!isValid(argv[1], &pos))
	{
		std::cout << "Error: Encountered unexpected character \'" << argv[1][pos] << "\'" << std::endl;
		return FAILURE;
	}
	Calculator calc(argv[1]);
	if (!calc.error())
		std::cout << calc.getResult() << std::endl;
	return SUCCESS;
}
