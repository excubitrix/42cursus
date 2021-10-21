#ifndef INCREMENT_H
# define INCREMENT_H

# include "IInstruction.hpp"
# include "MindOpen.hpp"

class	Increment: public IInstruction {

	public:

		Increment(void);
		Increment(Increment const &src);
		virtual ~Increment(void);

		Increment& operator=(Increment const& src);

		IInstruction*	clone(void);
		void			execute(MindOpen& mo);
};

#endif
