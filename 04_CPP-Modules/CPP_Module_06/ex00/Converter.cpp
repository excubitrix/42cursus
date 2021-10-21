#include "Converter.hpp"

Converter::Converter(char const* value) : _value(0) {
	int length = std::strlen(value);
	if (length == 1 && !std::isdigit(value[0]))
		this->_value = static_cast<double>(value[0]);
	else if (length == 3 && value[0] == '\'' && value[2] == '\'')
		this->_value = static_cast<double>(value[1]);
	else
	{
		bool dot = false;
		int i = (value[0] == '+' || value[0] == '-') ? 1 : 0;
		if (std::strcmp(&value[i], "nan") && std::strcmp(&value[i], "inf"))
		{
			for (int i = (value[0] == '+' || value[0] == '-') ? 1 : 0; i < length; i++)
			{
				if (value[i] == '.')
				{
					if (dot)
						throw BadArgumentException();
					dot = true;
				}
				else if (!std::isdigit(value[i]) && !(value[i] == 'f' && i == length -1))
					throw BadArgumentException();
			}
		}
		this->_value = std::atof(value);
	}
}

Converter::Converter(Converter const& src) {
	*this = src;
}

Converter::~Converter(void) {
}

Converter&	Converter::operator=(Converter const& src) {
	if (this != &src)
		this->_value = src._value;
	return *this;
}

const char*	Converter::BadArgumentException::what() const throw() {
	return "conversion not possible";
}

const char*	Converter::ImpossibleException::what() const throw() {
	return "impossible";
}

const char*	Converter::NonDisplayableException::what() const throw() {
	return "Non displayable";
}

char	Converter::toChar(void) const {
	int c = static_cast<int>(this->_value);
	if (this->_value == std::numeric_limits<double>::infinity()
		|| this->_value == -std::numeric_limits<double>::infinity()
		|| this->_value == NAN)
		throw ImpossibleException();
	if (c < 32 || c > 126)
		throw NonDisplayableException();
	return static_cast<char>(c);
}

int	Converter::toInt(void) const {
	long l = static_cast<long>(this->_value);
	if (l && (l > std::numeric_limits<int>::max()
		|| l < std::numeric_limits<int>::min()
		|| l == std::numeric_limits<long>::infinity()
		|| l == -std::numeric_limits<long>::infinity()
		|| l == NAN))
		throw ImpossibleException();
	return static_cast<int>(l);
}

float	Converter::toFloat(void) const {
	float f = static_cast<float>(this->_value);
	if ((f == std::numeric_limits<float>::infinity()
		&& this->_value != std::numeric_limits<double>::infinity())
		|| (f == -std::numeric_limits<float>::infinity()
		&& this->_value != -std::numeric_limits<double>::infinity())
		|| (f == NAN && this->_value != NAN))
		throw ImpossibleException();
	return f;
}

double	Converter::toDouble(void) const {
	return this->_value;
}

Converter::Converter(void) {
}

std::ostream&	operator<<(std::ostream& out, Converter const& obj) {
	try
	{
		char c = obj.toChar();
		out << "char: " << "\'" << c << "\'" << std::endl;
	}
	catch(const std::exception& e) { std::cerr << "char: " << e.what() << std::endl; }
	try
	{
		long i = obj.toInt();
		out << "int: " << i << std::endl;
	}
	catch(const std::exception& e) { std::cerr << "int: " << e.what() << std::endl; }
	try
	{
		float f = obj.toFloat();
		if (f - static_cast<int>(f) != 0.0f)
			out << "float: " << f << "f" << std::endl;
		else
			out << "float: " << f << ".0f" << std::endl;
	}
	catch(const std::exception& e) { std::cerr << "float: " << e.what() << std::endl; }
	try
	{
		double d = obj.toDouble();
		if (d - static_cast<int>(d) != 0.0)
			out << "doubel: " << d << std::endl;
		else
			out << "doubel: " << d << ".0" << std::endl;
	}
	catch(const std::exception& e) { std::cerr << "doubel: " << e.what() << std::endl; }
	return out;
}
