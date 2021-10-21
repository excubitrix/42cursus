#include "Token.hpp"
#include "Calculator.hpp"

Token::Token(int value, char op) : _value(value), _op(op) {
}

Token::Token(Token const& src) : _value(src._value), _op(src._op) {
}

Token::~Token(void) {
}

Token&	Token::operator=(Token const& src) {
	if (this != &src)
	{
		this->_value = src._value;
		this->_op = src._op;
	}
	return *this;
}

int		Token::getValue(void) const {
	return this->_value;
}

char	Token::getOp(void) const {
	return this->_op;
}
