#ifndef LOOPEND_H
# define LOOPEND_H

# include "IInstruction.hpp"
# include "MindOpen.hpp"

class	LoopEnd: public IInstruction {

	public:

		LoopEnd(void);
		LoopEnd(LoopEnd const &src);
		virtual ~LoopEnd(void);

		LoopEnd& operator=(LoopEnd const& src);

		IInstruction*	clone(void);
		void			execute(MindOpen& mo);
};

#endif
