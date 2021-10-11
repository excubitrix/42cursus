#include "FragTrap.hpp"

int		main(void)
{
	std::string	name1 = HONEY "Beep" RESET;
	std::string	name2 = PUKE_GREEN "Bop" RESET;

	FragTrap	beep(name1);
	FragTrap	bop(name2);

	beep.meleeAttack(name2);
	bop.takeDamage(30);
	bop.vaulthunter_dot_exe(name1);
	beep.takeDamage(50);
	beep.beRepaired(20);
	beep.rangedAttack(name2);
	bop.takeDamage(20);
	bop.beRepaired(20);
	bop.vaulthunter_dot_exe(name1);
	beep.takeDamage(50);
	beep.vaulthunter_dot_exe(name2);
	bop.takeDamage(50);
	beep.beRepaired(20);
	beep.beRepaired(20);
	bop.vaulthunter_dot_exe(name1);
	beep.takeDamage(50);
	bop.vaulthunter_dot_exe(name1);
	beep.takeDamage(50);
	bop.vaulthunter_dot_exe(name1);

	return 0;
}
