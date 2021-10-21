#ifndef DATA_H
# define DATA_H

#include <iostream>
#include <limits>

struct	Data {
	std::string	s1;
	int	i;
	std::string	s2;
};

void*	serialize(void);
Data*	deserialize(void* raw);

#endif
