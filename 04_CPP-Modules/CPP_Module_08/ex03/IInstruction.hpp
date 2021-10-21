#ifndef IINSTRUCTION_H
# define IINSTRUCTION_H

class	MindOpen;

class	IInstruction {

	public:

		virtual ~IInstruction(void) {}
		virtual IInstruction* clone(void) = 0;
		virtual void execute(MindOpen& mo) = 0;
};

#endif
