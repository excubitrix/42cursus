#ifndef WRITE_H
# define WRITE_H

# include "IInstruction.hpp"
# include "MindOpen.hpp"

class	Write: public IInstruction {

	public:

		Write(void);
		Write(Write const &src);
		virtual ~Write(void);

		Write& operator=(Write const& src);

		IInstruction*	clone(void);
		void			execute(MindOpen& mo);
};

#endif
