#include "SuperTrap.hpp"

int		main(void)
{
	std::string	name1 = HONEY "Beep" RESET;
	std::string	name2 = PUKE_GREEN "Bop" RESET;

	FragTrap	beep(name1);
	FragTrap	bop(name2);
	ScavTrap	bouncer(CYAN "Bouncer" RESET);
	NinjaTrap	ghost(BLACK "Ghost" RESET);
	NinjaTrap	ninja("Ninja");
	SuperTrap	clark(BRED "Clark" RESET);

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

	bouncer.challengeNewcomer();
	bouncer.rangedAttack("the newcomer");
	bouncer.takeDamage(30);
	bouncer.challengeNewcomer();
	bouncer.meleeAttack("the newcomer");
	bouncer.takeDamage(30);
	bouncer.beRepaired(20);
	bouncer.challengeNewcomer();
	bouncer.meleeAttack("the newcomer");
	bouncer.takeDamage(50);
	bouncer.takeDamage(50);

	ghost.meleeAttack("the target");
	ghost.rangedAttack("the target");
	ghost.takeDamage(55);
	ghost.beRepaired(60);
	ghost.ninjaShoebox(bop);
	ghost.ninjaShoebox(bouncer);
	ghost.ninjaShoebox(beep);
	ghost.ninjaShoebox(ninja);

	clark.meleeAttack(name1);
	clark.rangedAttack(name2);
	clark.takeDamage(15);
	clark.beRepaired(50);
	clark.FragTrap::vaulthunter_dot_exe(BLACK "Ghost" RESET);
	clark.NinjaTrap::ninjaShoebox(bouncer);

	return 0;
}
