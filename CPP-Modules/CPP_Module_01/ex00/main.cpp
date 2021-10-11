#include "Pony.hpp"

void	ponyOnTheStack(void)
{
	Pony	stack_pony("Stacky");

	stack_pony.train("stamina", 3);
	stack_pony.eat();
	stack_pony.eat();
	if (!stack_pony.train("speed", 7))
		stack_pony.train("speed", 6);
	stack_pony.sleep();
	stack_pony.train("trot", 6);
	stack_pony.eat();
	stack_pony.display_stats();
}

void	ponyOnTheHeap(void)
{
	Pony*	heap_pony = new Pony("Heapy");

	heap_pony->train("jumping", 3);
	heap_pony->train("gallop", 3);
	heap_pony->eat();
	heap_pony->sleep();
	heap_pony->train("gallop", 6);
	heap_pony->eat();
	heap_pony->sleep();
	heap_pony->display_stats();
	delete heap_pony;
}

int		main(void)
{
	std::cout << YELLOW "Entering ponyOnTheStack:" RESET << std::endl;
	ponyOnTheStack();
	std::cout << YELLOW "Entering ponyOnTheHeap:" RESET << std::endl;
	ponyOnTheHeap();
	std::cout << YELLOW "End of main() reached." RESET << std::endl;
	return 0;
}
