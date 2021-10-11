#ifndef EASYFIND_H
# define EASYFIND_H

# include <algorithm>

class NotFoundException : public std::exception {
    virtual const char* what() const throw() { return "Not found"; }
};

template <typename T>
typename T::iterator easyfind(T& arr, int n) {
    typename T::iterator it = std::find(arr.begin(), arr.end(), n);
	if (it == arr.end())
		throw NotFoundException();
	return it;
}

#endif
