#ifndef SCAVTRAP_H
# define SCAVTRAP_H

# include <iostream>

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36;1m"

class	ScavTrap {

	public:

		ScavTrap(std::string name);
		ScavTrap(ScavTrap const& src);
		~ScavTrap(void);

		ScavTrap&	operator=(ScavTrap const& src);

		void	meleeAttack(std::string const & target);
		void	rangedAttack(std::string const & target);

		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

		void	challengeNewcomer(void);

	protected:

		static std::string const	_announcement[6];
		static std::string const	_farewell[3];
		
		static std::string const	_prompt[5];
		static std::string const	_newcomer[5];

		std::string	_name;

		int		_hitPoints;
		int		_maxHitPoints;
		int		_engeryPoints;
		int		_maxEngeryPoints;
		int		_level;
		int		_meleeAttackDamage;
		int		_rangedAttackDamage;
		int		_armorDamageReduction;

		ScavTrap(void);
};

#endif
