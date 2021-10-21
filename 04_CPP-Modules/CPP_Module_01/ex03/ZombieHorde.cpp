#include "ZombieHorde.hpp"

ZombieHorde::ZombieHorde(int N) : _size(N) {
	srand(time(NULL));
	if (N > 0)
	{
		std::cout << "ZombieHorde parameter constructor called: "
				  << "You can hear a horde of zombies approaching..." << std::endl;
		this->_horde = new Zombie[N];
		for (int i = 0; i < N; i++)
		{
			_horde[i].setName(_gen_random(6));
			_horde[i].setType("horde");
		}
		return ;
	}
	std::cout << "ZombieHorde parameter constructor called: "
			  << "It's quiet. Too quiet..?" << std::endl;
}

ZombieHorde::~ZombieHorde(void) {
	if (this->_size > 0)
	{
		delete [] this->_horde;
		std::cout << "ZombieHorde destructor called: "
				  << "The zombie horde has been defeated." << std::endl;
		return ;
	}
	std::cout << "ZombieHorde destructor called: It's still quiet." << std::endl;
}

void	ZombieHorde::announce(void) const {
	if (this->_size > 0)
		for (int i = 0; i < this->_size; i++)
			_horde[i].announce();
}

std::string const ZombieHorde::_gen_random(const int len) const {
	std::string tmp;
    std::string const alpha = "abcdefghijklmnopqrstuvwxyz";

	tmp.reserve(len);

	for (int i = 0; i < len; ++i)
		tmp += alpha[rand() % alpha.length()];
	tmp[0] = std::toupper(tmp[0]);

	return tmp;
}
