#include "MiningBarge.hpp"

MiningBarge::MiningBarge(void) {
	for (int i = 0; i < 4; i++)
		this->_laser[i] = NULL;
}

MiningBarge::MiningBarge(MiningBarge const& src) {
	for (int i = 0; i < 4; i++)
		this->_laser[i] = NULL;
	*this = src;
}

MiningBarge::~MiningBarge(void) {
}

MiningBarge&	MiningBarge::operator=(MiningBarge const& src) {
	if (this != &src)
		for (int i = 0; i < 4; i++)
			this->_laser[i] = src._laser[i];
	return *this;
}

void	MiningBarge::equip(IMiningLaser* laser) {
	for (int i = 0; i < 4; i++)
	{
		if (!this->_laser[i])
		{
			this->_laser[i] = laser;
			break ;
		}
	}
}

void	MiningBarge::mine(IAsteroid* target) const {
	for (int i = 0; i < 4; i++)
		if (this->_laser[i])
			this->_laser[i]->mine(target);
}
