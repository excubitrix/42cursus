#ifndef PRINCESS_H
# define PRINCESS_H

# include <iostream>
# include "Victim.hpp"

class	Princess : public Victim {

	public:

		Princess(std::string name);
		Princess(Princess const& src);
		virtual ~Princess(void);

		Princess&	operator=(Princess const& src);

		void	getPolymorphed(void) const;

	private:

		Princess(void);
};

std::ostream&	operator<<(std::ostream& out, Princess const& src);

#endif
