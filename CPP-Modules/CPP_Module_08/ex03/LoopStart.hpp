#ifndef LOOPSTART_H
# define LOOPSTART_H

# include "IInstruction.hpp"
# include "MindOpen.hpp"

class	LoopStart: public IInstruction {

	public:

		LoopStart(void);
		LoopStart(LoopStart const &src);
		virtual ~LoopStart(void);

		LoopStart& operator=(LoopStart const& src);

		IInstruction*	clone(void);
		void			execute(MindOpen& mo);
};

#endif
