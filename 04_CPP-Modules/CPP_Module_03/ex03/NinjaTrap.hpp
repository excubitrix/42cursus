#ifndef NINJATRAP_H
# define NINJATRAP_H

# include "ClapTrap.hpp"
# include "FragTrap.hpp"
# include "ScavTrap.hpp"

class	NinjaTrap : public virtual ClapTrap {

	public:

		NinjaTrap(std::string name);
		NinjaTrap(NinjaTrap const& src);
		~NinjaTrap(void);

		NinjaTrap&	operator=(NinjaTrap const& src);

		void	meleeAttack(std::string const & target);
		void	rangedAttack(std::string const & target);

		void	ninjaShoebox(ClapTrap& ref);
		void	ninjaShoebox(FragTrap& ref);
		void	ninjaShoebox(ScavTrap& ref);
		void	ninjaShoebox(NinjaTrap& ref);

	protected:

		static std::string const	_announcement[6];
		static std::string const	_farewell[3];

	private:

		NinjaTrap(void);
};

#endif
