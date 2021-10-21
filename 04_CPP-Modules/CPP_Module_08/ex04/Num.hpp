#ifndef NUM_H
# define NUM_H

# include "Token.hpp"
# include "Calculator.hpp"

class	Num : public Token {

	public:

		Num(void);
		Num(int value);
		Num(Num const& src);
		virtual ~Num(void);

		Num&	operator=(Num const& src);

		std::string	getType(void);
		void		execute(Calculator& c);
};

#endif
