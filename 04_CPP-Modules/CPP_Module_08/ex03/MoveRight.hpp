#ifndef MOVERIGHT_H
# define MOVERIGHT_H

# include "IInstruction.hpp"
# include "MindOpen.hpp"

class	MoveRight: public IInstruction {

	public:

		MoveRight(void);
		MoveRight(MoveRight const &src);
		virtual ~MoveRight(void);

		MoveRight& operator=(MoveRight const& src);

		IInstruction*	clone(void);
		void			execute(MindOpen& mo);
};

#endif
