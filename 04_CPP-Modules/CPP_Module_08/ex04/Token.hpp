#ifndef TOKEN_H
# define TOKEN_H

# include <string>

class	Calculator;

class	Token {

	public:

		Token(void);
		Token(int value, char op);
		Token(Token const& src);
		virtual ~Token(void);

		Token&	operator=(Token const& src);

		int			getValue(void) const;
		char		getOp(void) const;

		virtual std::string	getType(void) = 0;
		virtual void		execute(Calculator&) = 0;

	protected:

		int			_value;
		char		_op;
};

#endif
