#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int	main(void)
{
	std::srand(std::time(NULL));

	for (int i = 0; i < 10; ++i)
	{
		Base	*base = generate();

		std::cout << "pointer: ";
		identify(base);
		std::cout << "reference: ";
		identify(*base);
		delete base;
	}
	return (0);
}
