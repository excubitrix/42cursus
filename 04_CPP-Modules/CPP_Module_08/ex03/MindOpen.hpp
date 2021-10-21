#ifndef MINDOPEN_H
# define MINDOPEN_H

# include <iostream>
# include <sstream>
# include <fstream>

# include <algorithm>
# include <vector>
# include <deque>

# include "IInstruction.hpp"
# include "Decrement.hpp"
# include "Increment.hpp"
# include "LoopEnd.hpp"
# include "LoopStart.hpp"
# include "MoveLeft.hpp"
# include "MoveRight.hpp"
# include "Read.hpp"
# include "Write.hpp"

class	MindOpen {

	public:

		MindOpen(const char* file);
		MindOpen(MindOpen const& src);
		virtual ~MindOpen(void);

		MindOpen&	operator=(MindOpen const& src);

		class SyntaxException : public std::exception {
			virtual const char*	what() const throw();
		};

		class KillException : public std::exception {
			virtual const char*	what() const throw();
		};

		char	getData(void);

		void	moveRight(void);
		void	moveLeft(void);
		void	increment(void);
		void	decrement(void);
		void	readData(void);
		void	writeData(void);
		void	next(void);
		void	repeat(void);

		void	execute(void);

	private:

		std::string					_code;

		size_t						_i;
		std::vector<char>			_array;

		size_t						_cur;
		std::deque<IInstruction*>	_instructions;

		void	_getInstructions(void);

		MindOpen(void);
};

#endif
