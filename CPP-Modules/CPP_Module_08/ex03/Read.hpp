#ifndef READ_H
# define READ_H

# include "IInstruction.hpp"
# include "MindOpen.hpp"

class	Read: public IInstruction {

	public:

		Read(void);
		Read(Read const &src);
		virtual ~Read(void);

		Read& operator=(Read const& src);

		IInstruction*	clone(void);
		void			execute(MindOpen& mo);
};

#endif
