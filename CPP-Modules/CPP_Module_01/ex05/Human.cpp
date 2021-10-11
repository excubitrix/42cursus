#include "Human.hpp"

Human::Human(void) {
	std::cout << "Human default constructor called" << std::endl;
}

Human::~Human(void) {
	std::cout << "Human destructor called" << std::endl;
}

std::string	Human::identify(void) {
	return this->_brain.identify(); 
}

Brain&	Human::getBrain(void) {
	return this->_brain;
}
