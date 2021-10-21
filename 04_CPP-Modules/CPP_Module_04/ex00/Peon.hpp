#ifndef PEON_H
# define PEON_H

# include <iostream>
# include "Victim.hpp"

class	Peon : public Victim {

	public:

		Peon(std::string name);
		Peon(Peon const& src);
		virtual ~Peon(void);

		Peon&	operator=(Peon const& src);

		void	getPolymorphed(void) const;

	private:

		Peon(void);
};

std::ostream&	operator<<(std::ostream& out, Peon const& src);

#endif
