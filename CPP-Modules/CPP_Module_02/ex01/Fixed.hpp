#ifndef FIXED_H
# define FIXED_H

# include <iostream>
# include <cmath>

class	Fixed {

	public:

		Fixed(void);
		Fixed(int const value);
		Fixed(float const value);
		Fixed(Fixed const& src);
		~Fixed(void);

		Fixed&	operator=(Fixed const& src);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);

		float	toFloat(void) const;
		int		toInt(void) const;

	private:

		static int const	_bits;

		int		_value;
};

std::ostream&	operator<<(std::ostream& out, Fixed const& src);

#endif
