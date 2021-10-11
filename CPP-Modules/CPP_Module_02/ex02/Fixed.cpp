#include "Fixed.hpp"

int const	Fixed::_bits = 8;

Fixed::Fixed(void) {
	this->_value = 0;
}

Fixed::Fixed(int const value) {
	this->_value = (value << this->_bits);
}

Fixed::Fixed(float const value) {
	this->_value = roundf(value * (1 << this->_bits));
}

Fixed::Fixed(Fixed const& src) {
	*this = src;
}

Fixed::~Fixed(void) {
}

Fixed&	Fixed::operator=(Fixed const& src) {
	if (this != &src)
		this->_value = src.getRawBits();
	return *this;
}

bool	Fixed::operator>(Fixed const& obj) {
	return (this->_value > obj.getRawBits());
}

bool	Fixed::operator<(Fixed const& obj) {
	return (this->_value < obj.getRawBits());
}

bool	Fixed::operator>=(Fixed const& obj) {
	return (this->_value >= obj.getRawBits());
}

bool	Fixed::operator<=(Fixed const& obj) {
	return (this->_value <= obj.getRawBits());
}

bool	Fixed::operator==(Fixed const& obj) {
	return (this->_value == obj.getRawBits());
}

bool	Fixed::operator!=(Fixed const& obj) {
	return (this->_value != obj.getRawBits());
}

Fixed	Fixed::operator+(Fixed const& obj) {
	Fixed tmp;
	tmp.setRawBits(this->_value + obj.getRawBits());
	return tmp;
}

Fixed	Fixed::operator-(Fixed const& obj) {
	Fixed tmp;
	tmp.setRawBits(this->_value - obj.getRawBits());
	return tmp;
}

Fixed	Fixed::operator*(Fixed const& obj) {
	Fixed tmp;
	tmp.setRawBits((this->_value * obj.getRawBits()) / (1 << this->_bits));
	return tmp;
}

Fixed	Fixed::operator/(Fixed const& obj) {
	Fixed tmp;
	tmp.setRawBits((this->_value * (1 << this->_bits)) / obj.getRawBits());
	return tmp;
}

Fixed	Fixed::operator++() {
	this->_value++;
	return *this;
}

Fixed	Fixed::operator++(int) {
	Fixed tmp = *this;
	operator++();
	return tmp;
}

Fixed	Fixed::operator--() {
	this->_value--;
	return *this;
}

Fixed	Fixed::operator--(int) {
	Fixed tmp = *this;
	operator--();
	return tmp;
}

int		Fixed::getRawBits(void) const {
	return this->_value;
}

void	Fixed::setRawBits(int const raw) {
	this->_value = raw;
}

float	Fixed::toFloat(void) const {
	return static_cast<float>(this->_value / static_cast<float>(1 << this->_bits));
}

int		Fixed::toInt(void) const {
	return this->_value >> this->_bits;
}

std::ostream&	operator<<(std::ostream& out, Fixed const& src) {
	out << src.toFloat();
	return out;
}

Fixed&	min(Fixed& a, Fixed& b) {
	return a < b ? a : b;
}

Fixed const&	min(Fixed const& a, Fixed const& b) {
	if (a.getRawBits() < b.getRawBits())
		return (a);
	return (b);
}

Fixed&	max(Fixed& a, Fixed& b) {
	return a > b ? a : b;
}

Fixed const&	max(Fixed const& a, Fixed const& b) {
	if (a.getRawBits() > b.getRawBits())
		return (a);
	return (b);
}
