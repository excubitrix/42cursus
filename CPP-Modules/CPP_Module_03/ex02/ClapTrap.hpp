#ifndef CLAPTRAP_H
# define CLAPTRAP_H

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
# define BLACK "\033[30;1m"
# define BRED "\033[31;1m"

class	ClapTrap {

	public:

		ClapTrap(std::string name);
		ClapTrap(std::string name, std::string type);
		ClapTrap(ClapTrap const& src);
		~ClapTrap(void);

		ClapTrap&	operator=(ClapTrap const& src);

		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

		std::string const	getName(void) const;

	protected:

		std::string	_name;

		int		_hitPoints;
		int		_maxHitPoints;
		int		_engeryPoints;
		int		_maxEngeryPoints;
		int		_level;
		int		_meleeAttackDamage;
		int		_rangedAttackDamage;
		int		_armorDamageReduction;

		std::string const	getType(void) const;

	private:
		
		std::string	_type;

		ClapTrap(void);
};

#endif
