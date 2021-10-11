#include <iostream>
#include "whatever.hpp"

#define RESET "\033[0m"
#define YELLOW "\033[33m"

class Awesome
{
    public:
        Awesome( int n ) : _n( n ) {}
        bool operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
        bool operator!=( Awesome const & rhs ) const{ return (this->_n != rhs._n); }
        bool operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
        bool operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
        bool operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
        bool operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
    
		int	get(void) const { return this->_n; }

    private:
        int _n;
};

std::ostream&	operator<<(std::ostream& out, Awesome const& obj) { out << obj.get(); return out; }

int	main()
{
	std::cout << YELLOW << "FROM SUBJECT" << RESET << std::endl;
	{
		int a = 2;
		int b = 3;

		::swap( a, b );
		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
		std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;

		std::string c = "chaine1";
		std::string d = "chaine2";

		::swap(c, d);
		std::cout << "c = " << c << ", d = " << d << std::endl;
		std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
		std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
	}
	std::cout << YELLOW << "COMPLEX TYPE" << RESET << std::endl;
	{
		Awesome a(19);
		Awesome b(42);

		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "*swap*" << std::endl;
		::swap(a, b);
		std::cout << "a = " << a << ", b = " << b << std::endl;

		std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
		std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
	}
	return 0;
}
