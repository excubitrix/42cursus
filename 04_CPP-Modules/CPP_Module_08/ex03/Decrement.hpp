#ifndef DECREMENT_H
# define DECREMENT_H

# include "IInstruction.hpp"
# include "MindOpen.hpp"

class	Decrement: public IInstruction {

	public:

		Decrement(void);
		Decrement(Decrement const &src);
		virtual ~Decrement(void);

		Decrement& operator=(Decrement const& src);

		IInstruction*	clone(void);
		void			execute(MindOpen& mo);
};

#endif
