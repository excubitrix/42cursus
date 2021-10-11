#include "AWeapon.hpp"

AWeapon::AWeapon(std::string const& name, int apcost, int damage) : _name(name), _apcost(apcost), _damage(damage) {
}

AWeapon::AWeapon(AWeapon const& src) : _name(src._name), _apcost(src._apcost), _damage(src._damage) {
}

AWeapon::~AWeapon(void) {
}

AWeapon&	AWeapon::operator=(AWeapon const& src) {
	if (this != &src)
	{
		this->_name = src._name;
		this->_apcost = src._apcost;
		this->_damage = src._damage;
	}
	return *this;
}

std::string	AWeapon::getName(void) const {
	return this->_name;
}

int	AWeapon::getAPCost(void) const {
	return this->_apcost;
}

int	AWeapon::getDamage(void) const {
	return this->_damage;
}

AWeapon::AWeapon(void) {
}
