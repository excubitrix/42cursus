#include "Data.hpp"

#define RESET "\033[0m"
#define YELLOW "\033[33m"

int		main(void)
{
	srand(time(NULL));

	for (int i = 0; i < 5; i++)
	{
		std::cout << YELLOW << "Test " << i << ":" << RESET << std::endl;

		void* raw = serialize();
		Data* data = deserialize(raw);

		std::cout << " s1: " << data->s1 << std::endl
				  << "int: " << data->i << std::endl
				  << " s2: " << data->s2 << std::endl;

		delete static_cast<char*>(raw);
		delete data;
	}

	return 0;
}
