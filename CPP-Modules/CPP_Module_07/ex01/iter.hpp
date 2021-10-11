#ifndef ITER_H
# define ITER_H

template<typename T>
void	iter(T (*arr), size_t length, void (*f)(T const&))
{
	for (size_t i = 0; i < length; i++)
		(*f)(arr[i]);
}

#endif
