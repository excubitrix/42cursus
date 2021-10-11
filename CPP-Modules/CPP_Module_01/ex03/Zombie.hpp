#ifndef ZOMBIE_H
# define ZOMBIE_H

# include <iostream>

class	Zombie {

	public:

		Zombie(std::string name, std::string type);
		Zombie(void);
		~Zombie(void);

		void	announce(void) const;
		void	setName(std::string name);
		void	setType(std::string type);

	private:

		static std::string const	_growl[4];

		std::string const	_get_growl(void) const;

		std::string	_name;
		std::string	_type;
};

#endif
