#ifndef OP_H
# define OP_H

# include "Token.hpp"
# include "Calculator.hpp"

class	Op : public Token {

	public:

		Op(void);
		Op(char op);
		Op(Op const& src);
		virtual ~Op(void);

		Op&	operator=(Op const& src);

		std::string	getType(void);
		void		execute(Calculator& c);
};

#endif
