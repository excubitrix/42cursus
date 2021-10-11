#include "Human.hpp"

std::string	const	Human::_action_name[3] = {
	"melee",
	"ranged",
	"shout"
};

Human::functionPtr	Human::_f[3] = {
	&Human::_meleeAttack,
	&Human::_rangedAttack,
	&Human::_intimidatingShout
};

void	Human::_meleeAttack(std::string const & target) {
	std::cout << "<Human> Swings a spiked club at the " + target + "." << std::endl;
}

void	Human::_rangedAttack(std::string const & target) {
	std::cout << "<Human> Shoots at the " + target + " from a distance." << std::endl;
}

void	Human::_intimidatingShout(std::string const & target) {
	std::cout << "<Human> Shouts at the " + target + " intimidatingly." << std::endl;
}

void	Human::action(std::string const & action_name, std::string const & target) {
	for (int i = 0; i < 3; i++)
		if (action_name == this->_action_name[i])
			(this->*_f[i])(target);
}
