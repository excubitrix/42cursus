#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Cure.hpp"
#include "Ice.hpp"

int		main(void)
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;

	Character mary("Mary");
	Character jane("Jane");

	mary.equip(src->createMateria("ice"));
	jane.equip(src->createMateria("cure"));

	mary.use(0, jane);
	mary.use(1, jane);
	mary = jane;
	mary.use(0, jane);

	delete src;

	std::cout << "~END~" << std::endl;

	return 0;
}
