#ifndef FRAGTRAP_H
# define FRAGTRAP_H

# include "ClapTrap.hpp"

class	FragTrap : public virtual ClapTrap {

	public:

		FragTrap(std::string name);
		FragTrap(FragTrap const& src);
		~FragTrap(void);

		FragTrap&	operator=(FragTrap const& src);

		void	meleeAttack(std::string const & target);
		void	rangedAttack(std::string const & target);

		void	vaulthunter_dot_exe(std::string const & target);

	protected:

		static std::string const	_announcement[6];
		static std::string const	_farewell[3];

		static std::string const	_specialAttack[5];

	private:

		FragTrap(void);
};

#endif
