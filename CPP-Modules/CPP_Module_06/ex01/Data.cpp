#include "Data.hpp"

void*	serialize(void) {
	int		size = 2 * sizeof(char*) + sizeof(int);
	char	*raw = new char[size];

	for (int i = 0; i < (int)sizeof(char*); ++i)
		raw[i] = rand() % 95 + 32;

	*reinterpret_cast<int*>(raw + sizeof(char*)) = rand() % __INT_MAX__;

	for (int i = sizeof(char*) + sizeof(int); i < size; ++i)
		raw[i] = rand() % 95 + 32;

	return raw;
}

Data*	deserialize(void* raw) {
	Data* data = new Data;

	data->s1 = std::string(reinterpret_cast<char*>(raw), sizeof(char*));
	data->i = *reinterpret_cast<int*>(static_cast<char*>(raw) + sizeof(char*));
	data->s2 = std::string(reinterpret_cast<char*>(raw) + sizeof(char*) + sizeof(int), sizeof(char*));

	return data;
}
