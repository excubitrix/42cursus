#ifndef OPEN_H
# define OPEN_H

# include "Token.hpp"
# include "Calculator.hpp"

class	Open : public Token {

	public:

		Open(void);
		Open(Open const& src);
		virtual ~Open(void);

		Open&	operator=(Open const& src);

		std::string	getType(void);
		void		execute(Calculator& c);
};

#endif
