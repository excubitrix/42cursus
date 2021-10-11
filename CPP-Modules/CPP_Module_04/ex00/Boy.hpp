#ifndef BOY_H
# define BOY_H

# include <iostream>
# include "Victim.hpp"

class	Boy : public Victim {

	public:

		Boy(std::string name);
		Boy(Boy const& src);
		virtual ~Boy(void);

		Boy&	operator=(Boy const& src);

		void	getPolymorphed(void) const;

	private:

		Boy(void);
};

std::ostream&	operator<<(std::ostream& out, Boy const& src);

#endif
