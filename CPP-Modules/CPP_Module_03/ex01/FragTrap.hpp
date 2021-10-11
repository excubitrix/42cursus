#ifndef FRAGTRAP_H
# define FRAGTRAP_H

# include <iostream>

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36;1m"
# define HONEY "\e[38;5;214;1m"
# define PUKE_GREEN "\e[38;5;70;1m"

class	FragTrap {

	public:

		FragTrap(std::string name);
		FragTrap(FragTrap const& src);
		~FragTrap(void);

		FragTrap&	operator=(FragTrap const& src);

		void	meleeAttack(std::string const & target);
		void	rangedAttack(std::string const & target);

		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

		void	vaulthunter_dot_exe(std::string const & target);

	private:

		static std::string const	_announcement[6];
		static std::string const	_farewell[3];

		static std::string const	_specialAttack[5];

		std::string	_name;

		int		_hitPoints;
		int		_maxHitPoints;
		int		_engeryPoints;
		int		_maxEngeryPoints;
		int		_level;
		int		_meleeAttackDamage;
		int		_rangedAttackDamage;
		int		_armorDamageReduction;

		FragTrap(void);
};

#endif
