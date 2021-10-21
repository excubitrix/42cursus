#include "Fixed.hpp"

int 	main(void)
{
	{
		std::cout << std::endl << "*------from Subject------*" << std::endl << std::endl;

		Fixed a;
		Fixed const b(Fixed(5.05f) * Fixed(2));

		std::cout << a << std::endl;
		std::cout << ++a << std::endl;
		std::cout << a << std::endl;
		std::cout << a++ << std::endl;
		std::cout << a << std::endl;

		std::cout << b << std::endl;

		std::cout << max(a, b) << std::endl;
	}
	{
		std::cout << std::endl << "*------Extra------*" << std::endl << std::endl;

		Fixed a(4);
		Fixed b(5);

		std::cout << a << " + " << b << " = " << (a + b) << std::endl;
		std::cout << a << " - " << b << " = " << (a - b) << std::endl;
		std::cout << a << " * " << b << " = " << (a * b) << std::endl;
		std::cout << a << " / " << b << " = " << (a / b) << std::endl << std::endl;
		
		std::cout << b << std::endl;
		std::cout << --b << std::endl;
		std::cout << b << std::endl;
		std::cout << b-- << std::endl;
		std::cout << b << std::endl << std::endl;
		
		Fixed c(3.1f);
		Fixed d(-5.9f);

		std::cout << "a = " << c << ", b = " << d << std::endl << std::endl;
		std::cout << "min: " << min(c, d) << std::endl;
		std::cout << "max: " << max(c, d) << std::endl << std::endl;

		b++;
		b++;

		std::cout << a << std::setw(4) << " > " << b << " ? " << (a > b) << std::endl;
		std::cout << a << std::setw(4) << " < " << b << " ? " << (a < b) << std::endl;
		std::cout << a << " >= " << b << " ? " << (a >= b) << std::endl;
		std::cout << a << " <= " << b << " ? " << (a <= b) << std::endl;
		std::cout << a << " == " << b << " ? " << (a == b) << std::endl;
		std::cout << a << " != " << b << " ? " << (a != b) << std::endl;

		std::cout  << std::endl;
	}
	return 0;
}
