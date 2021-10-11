#ifndef BRAIN_H
# define BRAIN_H

# include <iostream>
# include <sstream>

class	Brain {

	public:
	
		Brain(void);
		~Brain(void);

		std::string		identify(void);

	private:

		static std::string const	_sides[2];

		std::string	const	_getDominantSide(void) const;

		std::string	_dominantSide;
};

#endif
