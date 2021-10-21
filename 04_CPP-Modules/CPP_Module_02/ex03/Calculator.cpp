#include "Calculator.hpp"

std::string const	Calculator::_opStr[4] = {
	"+",
	"-",
	"*",
	"/"
};

Calculator::functionPtr const	Calculator::_opPtr[4] = {
	&Fixed::operator+,
	&Fixed::operator-,
	&Fixed::operator*,
	&Fixed::operator/,
};

Calculator::Calculator(std::string expr) : _size_v(0), _size_o(0), _activeBraces(0), _lastTokenWasAValue(0), _error(1) {
	this->_size = _countTokens(expr);
	if (this->_size > 0)
	{
		Fixed		values[this->_size];
		std::string	ops[this->_size];
		this->_values = values;
		this->_ops = ops;
		this->_evaluate(expr);
	}
}

Calculator::Calculator(Calculator const& src) {
	*this = src;
}

Calculator::~Calculator(void) {
}

Calculator&	Calculator::operator=(Calculator const& src) {
	if (this != &src)
	{
		this->_values = src._values;
		this->_ops = src._ops;
		this->_size_v = src._size_v;
		this->_size_o = src._size_o;
		this->_activeBraces = src._activeBraces;
		this->_lastTokenWasAValue = src._lastTokenWasAValue;
		this->_result = src._result;
		this->_error = src._error;
	}
	return *this;
}

Fixed	Calculator::getResult(void) const {
	return this->_result;
}
int		Calculator::error(void) const {
	return this->_error;
}

int		Calculator::_countTokens(std::string s) {
	int i = 0;
	std::istringstream iss(s);
	while (iss) {
		std::string sub;
		iss >> sub;
		if (sub == std::string())
			break ;
		i++;
	}
	return i;
}

void	Calculator::_evaluate(std::string expr) {
	std::istringstream iss(expr);
	while (iss) {
		std::string sub;
		iss >> sub;
		if (sub == std::string())
			break ;
		if (!sub.compare("("))
		{
			this->_ops[this->_size_o++] = sub;
			this->_activeBraces++;
			this->_lastTokenWasAValue = -1;
		}
		else if (_isValue(sub))
		{
			if (_storeValue(sub) != SUCCESS)
				return ;
			this->_lastTokenWasAValue = 1;
		}
		else if (this->_activeBraces && !sub.compare(")") && this->_lastTokenWasAValue >= 0)
		{
			while (this->_size_o && this->_ops[this->_size_o - 1].compare("("))
				_doOp();
			if (this->_size_o)
			{
				this->_size_o--;
				this->_activeBraces--;
			}
		}
		else if (_weight(sub) && this->_lastTokenWasAValue)
		{
			while (this->_size_o && _weight(this->_ops[this->_size_o - 1]) >= _weight(sub))
				_doOp();
			this->_ops[this->_size_o++] = sub;
			this->_lastTokenWasAValue = 0;
		}
		else
		{
			std::cout << "Syntax error near \'" + sub + "\'" << std::endl;
			return ;
		}
	}
	while (this->_size_o)
		_doOp();
	if (this->_activeBraces)
	{
		std::cout << "Syntax error near \'" + this->_ops[this->_size_o] + "\'" << std::endl;
		return ;
	}
	this->_result = this->_values[0];
	this->_error = 0;
}

int		Calculator::_toInt(std::string s) {
	int result;
	std::stringstream ss;
	ss << s;
	ss >> result;
	return result;
}

float	Calculator::_toFloat(std::string s) {
	float result;
	std::stringstream ss;
	ss << s;
	ss >> result;
	return result;
}

bool	Calculator::_isValue(std::string s) {
	if (((isdigit(s[0]) || s[0] == '.') && this->_lastTokenWasAValue != 1)
		|| ((s[0] == '+' || s[0] == '-') && (isdigit(s[1]) || s[1] == '.')
			&& this->_lastTokenWasAValue != 1))
		return true;
	return false;
}

int		Calculator::_storeValue(std::string val) {
	size_t i = 0;
	int	isfloat = 0;
	if (val[i] == '+' || val[i] == '-')
		i++;
	while (val[i])
	{
		if (val[i] == '.')
			isfloat++;
		if ((!isdigit(val[i]) && val[i] != '.') || isfloat > 1)
		{
			std::cout << "Syntax error near \'" + val + "\'" << std::endl;
			return FAILURE;
		}
		i++;
	}
	if (!isfloat)
		this->_values[this->_size_v++] = Fixed(this->_toInt(val));
	else
		this->_values[this->_size_v++] = Fixed(this->_toFloat(val));
	return SUCCESS;
}

int	Calculator::_weight(std::string op) {
    if (!op.compare("+") || !op.compare("-"))
    	return 1;
    if (!op.compare("*") || !op.compare("/"))
    	return 2;
    return 0;
}

Fixed	Calculator::_applyOp(Fixed& obj1, Fixed& obj2, std::string op) {
	for (int i = 0; i < 4; i++)
		if (op == this->_opStr[i])
			return (obj1.*this->_opPtr[i])(obj2);
	return obj1;
}

void	Calculator::_doOp() {
	this->_size_v -= 2;
	this->_values[this->_size_v] = this->_applyOp(this->_values[this->_size_v],
		this->_values[this->_size_v + 1], this->_ops[--this->_size_o]);
	this->_size_v++;
}

Calculator::Calculator(void) {
	std::cout << "Calculator default constructor called" << std::endl;
}
