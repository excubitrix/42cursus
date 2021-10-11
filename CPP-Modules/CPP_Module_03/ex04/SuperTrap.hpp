#ifndef SUPERTRAP_H
# define SUPERTRAP_H

# include "ClapTrap.hpp"
# include "FragTrap.hpp"
# include "ScavTrap.hpp"
# include "NinjaTrap.hpp"

class	SuperTrap : public virtual FragTrap, public virtual NinjaTrap {

	public:

		SuperTrap(std::string name);
		SuperTrap(SuperTrap const& src);
		~SuperTrap(void);

		SuperTrap&	operator=(SuperTrap const& src);

		void	meleeAttack(std::string const & target);
		void	rangedAttack(std::string const & target);

		void	vaulthunter_dot_exe(std::string const & target);

	protected:
		
		std::string	_announcement(int const i) const;
		std::string	_farewell(int const i) const;

	private:

		SuperTrap(void);
};

#endif
