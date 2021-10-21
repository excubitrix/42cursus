#ifndef CONVERTER_H
# define CONVERTER_H

# include <iostream>
# include <limits>
# include <cmath>

class	Converter {

	public:

		Converter(char const* value);
		Converter(Converter const& src);
		virtual ~Converter(void);

		Converter&	operator=(Converter const& src);

		class BadArgumentException : public std::exception {
			virtual const char*	what() const throw();
		};

		class ImpossibleException : public std::exception {
			virtual const char*	what() const throw();
		};

		class NonDisplayableException : public std::exception {
			virtual const char*	what() const throw();
		};

		char	toChar(void) const;
		int		toInt(void) const;
		float	toFloat(void) const;
		double	toDouble(void) const;

	private:

		double	_value;

		Converter(void);
};

std::ostream&	operator<<(std::ostream& out, Converter const& obj);

#endif
