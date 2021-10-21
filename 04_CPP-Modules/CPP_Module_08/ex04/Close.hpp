#ifndef CLOSE_H
# define CLOSE_H

# include "Token.hpp"
# include "Calculator.hpp"

class	Close : public Token {

	public:

		Close(void);
		Close(Close const& src);
		virtual ~Close(void);

		Close&	operator=(Close const& src);

		std::string	getType(void);
		void		execute(Calculator& c);
};

#endif
