#ifndef FIXED_H
# define FIXED_H

# include <iostream>
# include <iomanip>
# include <cmath>

class	Fixed {

	public:

		Fixed(void);
		Fixed(int const value);
		Fixed(float const value);
		Fixed(Fixed const& src);
		~Fixed(void);

		Fixed&	operator=(Fixed const& src);

		bool	operator>(Fixed const& obj);
		bool	operator<(Fixed const& obj);
		bool	operator>=(Fixed const& obj);
		bool	operator<=(Fixed const& obj);
		bool	operator==(Fixed const& obj);
		bool	operator!=(Fixed const& obj);

		Fixed	operator+(Fixed const& obj);
		Fixed	operator-(Fixed const& obj);
		Fixed	operator*(Fixed const& obj);
		Fixed	operator/(Fixed const& obj);

		Fixed	operator++();
		Fixed	operator++(int);
		Fixed	operator--();
		Fixed	operator--(int);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);

		float	toFloat(void) const;
		int		toInt(void) const;

	private:

		static int const	_bits;

		int		_value;
};

std::ostream&	operator<<(std::ostream& out, Fixed const& src);

Fixed&			min(Fixed& a, Fixed& b);
Fixed const&	min(Fixed const& a, Fixed const& b);
Fixed&			max(Fixed& a, Fixed& b);
Fixed const&	max(Fixed const& a, Fixed const& b);

#endif
