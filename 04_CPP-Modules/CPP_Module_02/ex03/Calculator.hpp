#ifndef CALCULATOR_H
# define CALCULATOR_H

# include <iostream>
# include <sstream>
# include <string>
# include <cmath>
# include "Fixed.hpp"

# define SUCCESS 0
# define FAILURE 1

class	Calculator {

	public:

		typedef		Fixed(Fixed::*functionPtr)(Fixed const& obj);

		Calculator(std::string expr);
		Calculator(Calculator const& src);
		~Calculator(void);

		Calculator&	operator=(Calculator const& src);

		Fixed	getResult(void) const;
		int		error(void) const;

	private:

		static std::string const	_opStr[4];
		static functionPtr const	_opPtr[4];

		int				_size;
		Fixed*			_values;
		std::string*	_ops;

		int		_size_v;
		int		_size_o;
		int		_activeBraces;
		int		_lastTokenWasAValue;

		Fixed	_result;
		int		_error;

		int		_countTokens(std::string s);
		void	_evaluate(std::string expr);

		int		_toInt(std::string s);
		float	_toFloat(std::string s);

		bool	_isValue(std::string s);
		int		_storeValue(std::string val);

		int		_weight(std::string op);

		Fixed	_applyOp(Fixed& obj1, Fixed& obj2, std::string op);
		void	_doOp();

		Calculator(void);
};

#endif
