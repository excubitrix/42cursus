#include "Brain.hpp"

std::string const	Brain::_sides[2] = {
	"left",
	"right"
};

std::string	const	Brain::_getDominantSide(void) const {
	return this->_sides[rand() % 2];
}

Brain::Brain(void) {
	this->_dominantSide = _getDominantSide();
	std::cout << "Brain default constructor called: A " + this->_dominantSide
			  << "-brainer identified by " + this->identify()
			  << " is born." << std::endl;
}

Brain::~Brain(void) {
	std::cout << "Brain destructor called: The " + this->_dominantSide
			  << "-brainer identified by " + this->identify()
			  << " died." << std::endl;
}

std::string	Brain::identify(void) {
	std::ostringstream	id;

	id << this;
	return id.str();
}
