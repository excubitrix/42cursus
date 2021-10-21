#include "Enemy.hpp"

Enemy::Enemy(int hp, std::string const& type) : _type(type), _hp(hp) {
}

Enemy::Enemy(Enemy const& src) : _type(src._type), _hp(src._hp) {
}

Enemy::~Enemy(void) {
}

Enemy&	Enemy::operator=(Enemy const& src) {
	if (this != &src)
	{
		this->_type = src._type;
		this->_hp = src._hp;
	}
	return *this;
}

std::string	Enemy::getType(void) const {
	return this->_type;
}

int		Enemy::getHP(void) const {
	return this->_hp;
}

void	Enemy::takeDamage(int amount) {
	if (amount < 0)
		return ;
	this->_hp -= amount;
	if (this->_hp < 0)
		this->_hp = 0;
}

Enemy::Enemy(void) {
}
