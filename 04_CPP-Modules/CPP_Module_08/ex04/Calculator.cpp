#include "Calculator.hpp"

Calculator::Calculator(std::string expr) {
	expr.erase(std::remove(expr.begin(), expr.end(), ' '), expr.end());
	if (expr.find_first_not_of("0123456789+-/*()") != std::string::npos)
		throw UnexpectedCharacterException();
	int	openBraces = 0;
	int	lastTokenWasValue = 0;
	for (size_t i = 0; i < expr.length(); i++)
	{
		int type = this->_getType(expr[i]);
		if (type == OP && i && lastTokenWasValue)
		{
			this->_tokens.push_back(new Op(expr[i]));
			lastTokenWasValue = 0;
		}
		else if ((type == NUM || ((expr[i] == '+' || expr[i] == '-') && std::isdigit(expr[i + 1]))) && lastTokenWasValue != 1)
		{
			std::stringstream ss;
			if (expr[i] == '+' || expr[i] == '-')
				ss << expr[i++];
			while (std::isdigit(expr[i]))
				ss << expr[i++];
			i--;
			int value;
			ss >> value;
			if (ss.fail())
			{
				this->deleteList(this->_tokens);
				throw InvalidNumberException();
			}
			this->_tokens.push_back(new Num(value));
			lastTokenWasValue = 1;
			ss.str(std::string());
			ss.clear();
		}
		else if (type == '(')
		{
			this->_tokens.push_back(new Open());
			openBraces++;
			lastTokenWasValue = -1;
		}
		else if (type == ')' && openBraces && lastTokenWasValue >= 0)
		{
			this->_tokens.push_back(new Close());
			openBraces--;
		}
		else
		{
			this->deleteList(this->_tokens);
			throw SyntaxErrorException();
		}
	}
	if (openBraces || !lastTokenWasValue)
	{
		this->deleteList(this->_tokens);
		throw SyntaxErrorException();
	}
	this->_genPostfix();
}

Calculator::Calculator(Calculator const& src) {
	*this = src;
}

void	Calculator::deleteList(std::list<Token*> list) {
	std::list<Token*>::const_iterator it;
	for (it = list.begin(); it != list.end(); it++)
		delete *it;
	list.clear();
}

Calculator::~Calculator(void) {
	while (!this->_values.empty())
		this->_values.pop();
	this->deleteList(this->_tokens);
	this->deleteList(this->_postfix);
}

Calculator&	Calculator::operator=(Calculator const& src) {
	if (this != &src)
	{
		while (!this->_values.empty())
			this->_values.pop();
		std::copy(src._values.begin(), src._values.end(), this->_values.begin());
		this->deleteList(this->_tokens);
		std::copy(src._tokens.begin(), src._tokens.end(), this->_tokens.begin());
		this->deleteList(this->_postfix);
		std::copy(src._postfix.begin(), src._postfix.end(), this->_postfix.begin());
	}
	return *this;
}

const char*	Calculator::UnexpectedCharacterException::what() const throw() {
	return "encountered unexpected character";
}

const char*	Calculator::InvalidNumberException::what() const throw() {
	return "invalid number";
}

const char*	Calculator::SyntaxErrorException::what() const throw() {
	return "syntax error";
}

const char*	Calculator::DivisionByZeroException::what() const throw() {
	return "division by zero";
}

const char*	Calculator::UnknownOperatorException::what() const throw() {
	return "unknown operator";
}

void	printType(Token* t) {
	std::cout << t->getType() << " ";
}

void	Calculator::displayTokens(void) const {
	std::cout << "Tokens: ";
	std::for_each(this->_tokens.begin(), this->_tokens.end(), printType);
	std::cout << "\b" << std::endl;
}

void	Calculator::displayPostfix(void) const {
	std::cout << "Postfix: ";
	std::for_each(this->_postfix.begin(), this->_postfix.end(), printType);
	std::cout << "\b" << std::endl;
}

void	printInt(const int& n) {
	std::cout << n << " ";
}

void	Calculator::evaluate(void) {
	std::list<Token*>::const_iterator it;
	for (it = this->_postfix.begin(); it != this->_postfix.end(); it++)
	{
		std::cout << "I " << std::setw(16) << std::left << (*it)->getType() << "| OP ";
		(*it)->execute(*this);
		std::cout << "| ST ";
		std::for_each(this->_values.rbegin(), this->_values.rend(), printInt);
		std::cout << "\b]" << std::endl;
	}
	std::cout << "Result : " << this->_values.top() << std::endl;
	this->_values.pop();
}

int		Calculator::_getType(char c) {
	if (c == '+' || c == '-' || c == '/' || c == '*')
		return OP;
	if (std::isdigit(c))
		return NUM;
	return c;
}

int	Calculator::_getPriority(char op) {
    if (op == '+' || op == '-')
    	return 1;
    if (op == '/' || op == '*')
    	return 2;
    return 0;
}

void	Calculator::_genPostfix(void) {
	std::stack<Token*> stack;
	std::list<Token*>::iterator it;
	for (it = this->_tokens.begin(); it != this->_tokens.end(); ++it)
	{
		if (dynamic_cast<Num*>(*it))
		{
			this->_postfix.push_back(new Num((*it)->getValue()));
			
		}
		else if (dynamic_cast<Open*>(*it))
			stack.push(new Open());
		else if (dynamic_cast<Close*>(*it))
		{
			while (!dynamic_cast<Open*>(stack.top()))
			{
				this->_postfix.push_back(stack.top());
				stack.pop();
			}
			delete stack.top();
			stack.pop();
		}
		else if (dynamic_cast<Op*>(*it))
		{
			while (!stack.empty() && this->_getPriority((*it)->getOp()) <= this->_getPriority(stack.top()->getOp()))
			{
				this->_postfix.push_back(stack.top());
				stack.pop();
			}
			stack.push(new Op((*it)->getOp()));
		}
	}
	while (!stack.empty())
	{
		this->_postfix.push_back(stack.top());
		stack.pop();
	}
}

void	Calculator::push(int value) {
	this->_values.push(value);
}

void	Calculator::applyOp(char op) {
	int val2 = this->_values.top();
	this->_values.pop();
	int val1 = this->_values.top();
	this->_values.pop();
	switch (op)
	{
		case '+' :
			this->_values.push(val1 + val2);
			break;
		case '-' :
			this->_values.push(val1 - val2);
			break;
		case '/' :
			if (!val2)
				throw DivisionByZeroException();
			this->_values.push(val1 / val2);
			break;
		case '*' :
			this->_values.push(val1 * val2);
			break;
		default :
			throw UnknownOperatorException();
	}
}
