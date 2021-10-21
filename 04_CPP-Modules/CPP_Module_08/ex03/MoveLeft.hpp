#ifndef MOVELEFT_H
# define MOVELEFT_H

# include "IInstruction.hpp"
# include "MindOpen.hpp"

class	MoveLeft: public IInstruction {

	public:

		MoveLeft(void);
		MoveLeft(MoveLeft const &src);
		virtual ~MoveLeft(void);

		MoveLeft& operator=(MoveLeft const& src);

		IInstruction*	clone(void);
		void			execute(MindOpen& mo);
};

#endif
