#include "Squad.hpp"

Squad::Squad(void) : _N(0), _unit(NULL) {
}

Squad::Squad(Squad const& src) : _N(0), _unit(NULL) {
	*this = src;
}

Squad::~Squad(void) {
	while (this->_unit)
	{
		t_unit* tmp = this->_unit->next;
		delete this->_unit->marine;
		delete this->_unit;
		this->_unit = tmp;
	}
}

Squad&	Squad::operator=(Squad const& src) {
	if (this != &src)
	{
		while (this->_unit)
		{
			t_unit* tmp = this->_unit->next;
			delete this->_unit->marine;
			delete this->_unit;
			this->_unit = tmp;
		}
		this->_N = 0;
		for (int i = 0; i < src.getCount(); i++)
			this->push(src.getUnit(i)->clone());
	}
	return *this;
}

int	Squad::getCount(void) const {
	return this->_N;
}

ISpaceMarine*	Squad::getUnit(int N) const {
	if (this->_N == 0 || N < 0 || N >= this->_N)
		return NULL;
	t_unit* tmp = this->_unit;
	for (int i = 0; i < N; i++)
		tmp = tmp->next;
	return tmp->marine;
}

int	Squad::push(ISpaceMarine* marine) {
	if (!marine)
		return this->_N;
	if (!this->_unit)
	{
		this->_unit = new t_unit;
		this->_unit->marine = marine; 
		this->_unit->next = NULL;
	}
	else
	{
		t_unit* tmp = this->_unit;
		while (tmp->next)
		{
			if (&tmp->marine == &marine)
				return this->_N;
			tmp = tmp->next;
		}
		tmp->next = new t_unit;
		tmp->next->marine = marine; 
		tmp->next->next = NULL;
	}
	return ++this->_N;
}
