#include <iostream>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base*	generate(void) {

	int r = rand() % 100;

	if (r < 33)
		return (new A);
	if (r < 66)
		return (new B);
	return (new C);
}

void	identify_from_pointer(Base* p) {
	if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}

void	identify_from_reference(Base& p) {
	identify_from_pointer(&p);
}

int		main(void)
{
	srand(time(NULL));

	for (int i = 0; i < 5; i++)
	{
		Base* obj = generate();
		
		std::cout << "Test " << i << ":" << std::endl;

		identify_from_pointer(obj);
		identify_from_reference(*obj);

		delete obj;
	}

	return 0;
}
