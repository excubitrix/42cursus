#ifndef CALCULATOR_H
# define CALCULATOR_H

# include <iostream>
# include <iomanip>
# include <sstream>

# include <algorithm>
# include "MutantStack.hpp"
# include <list>
 
# include "Close.hpp"
# include "Open.hpp"
# include "Num.hpp"
# include "Op.hpp"

# define OP 0
# define NUM 1

class	Calculator {

	public:

		Calculator(void);
		Calculator(std::string expr);
		Calculator(Calculator const& src);
		~Calculator(void);

		Calculator&	operator=(Calculator const& src);

		class UnexpectedCharacterException : public std::exception {
			virtual const char*	what() const throw();
		};

		class InvalidNumberException : public std::exception {
			virtual const char*	what() const throw();
		};

		class SyntaxErrorException : public std::exception {
			virtual const char*	what() const throw();
		};

		class DivisionByZeroException : public std::exception {
			virtual const char*	what() const throw();
		};

		class UnknownOperatorException : public std::exception {
			virtual const char*	what() const throw();
		};

		void	displayTokens(void) const;
		void	displayPostfix(void) const;
		void	evaluate(void);

		void	push(int value);
		void	applyOp(char op);

		void	deleteList(std::list<Token*> list);

	private:

		int		_getType(char c);
		int		_getPriority(char op);
		void	_genPostfix(void);

		MutantStack<int>	_values;
		std::list<Token*>	_tokens;
		std::list<Token*>	_postfix;
};

void	printType(Token* t);
void	printInt(int const& n);

#endif
