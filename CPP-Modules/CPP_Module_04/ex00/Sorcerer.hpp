#ifndef SORCERER_H
# define SORCERER_H

# include <iostream>
# include "Victim.hpp"

class	Sorcerer {

	public:

		Sorcerer(std::string name, std::string title);
		Sorcerer(Sorcerer const& src);
		~Sorcerer(void);

		Sorcerer&	operator=(Sorcerer const& src);

		std::string	getName(void) const;
		std::string	getTitle(void) const;

		void		polymorph(Victim const& victim) const;

	private:

		std::string	_name;
		std::string	_title;

		Sorcerer(void);
};

std::ostream&	operator<<(std::ostream& out, Sorcerer const& src);

#endif
