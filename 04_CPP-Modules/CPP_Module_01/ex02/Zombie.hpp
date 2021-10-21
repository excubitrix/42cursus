#ifndef ZOMBIE_H
# define ZOMBIE_H

# include <iostream>

class	Zombie {

	public:

		Zombie(std::string name, std::string type);
		~Zombie(void);

		void	announce(void) const;

	private:

		static std::string const	_growl[4];

		std::string const	_get_growl(void) const;

		std::string	_name;
		std::string	_type;
};

#endif
