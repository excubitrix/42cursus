#ifndef SCAVTRAP_H
# define SCAVTRAP_H

# include "ClapTrap.hpp"

class	ScavTrap : public virtual ClapTrap {

	public:

		ScavTrap(std::string name);
		ScavTrap(ScavTrap const& src);
		~ScavTrap(void);

		ScavTrap&	operator=(ScavTrap const& src);

		void	meleeAttack(std::string const & target);
		void	rangedAttack(std::string const & target);

		void	challengeNewcomer(void);

	protected:

		static std::string const	_announcement[6];
		static std::string const	_farewell[3];
		
		static std::string const	_prompt[5];
		static std::string const	_newcomer[5];

	private:

		ScavTrap(void);
};

#endif
