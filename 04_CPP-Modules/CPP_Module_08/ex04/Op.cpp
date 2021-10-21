#include "Op.hpp"

Op::Op(char op) : Token(0, op) {
}

Op::Op(Op const& src) : Token(0, src._op) {
	*this = src;
}

Op::~Op(void) {
}

Op&	Op::operator=(Op const& src) {
	if (this != &src)
		this->_op = src._op;
	return *this;
}

std::string	Op::getType(void) {
	std::stringstream ss;
	ss << "Op(" << this->_op << ")";
	return ss.str();
}

void	Op::execute(Calculator& c) {
	switch (this->_op)
	{
		case '+' :
			std::cout << "Add\t";
			break;
		case '-' :
			std::cout << "Subtract\t";
			break;
		case '/' :
			std::cout << "Divide\t";
			break;
		case '*' :
			std::cout << "Multiply\t";
			break;
	}
	c.applyOp(this->_op);
}
