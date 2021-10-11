#ifndef DIRECTORY_H
# define DIRECTORY_H

# include <iostream>
# include <iomanip>
# include <limits>
# include "Contact.hpp"

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"

# define LIMIT 8

class	Directory {

	public:

		Directory(void);
		~Directory(void);

		bool	add_contact(void);
		void	display_contacts(void);
		bool	search_contact(void);

	private:

		static int	_num;

		std::string	_truncate(std::string str, size_t width);

		Contact		_contact[LIMIT];
};

#endif
