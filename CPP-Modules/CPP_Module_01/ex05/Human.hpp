#ifndef HUMAN_H
# define HUMAN_H

# include <iostream>
# include "Brain.hpp"

class	Human {

	public:
	
		Human(void);
		~Human(void);

		std::string	identify(void);
		Brain&		getBrain(void);

	private:

		Brain	_brain;
};

#endif
