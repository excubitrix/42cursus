#ifndef FIXED_H
# define FIXED_H

# include <iostream>

class	Fixed {

	public:

		Fixed(void);
		Fixed(Fixed const& src);
		~Fixed(void);

		Fixed&	operator=(Fixed const& src);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);

	private:

		static int const	_bits;

		int		_value;
};

#endif
