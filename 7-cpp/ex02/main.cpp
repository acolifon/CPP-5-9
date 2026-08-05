#include "Array.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#define MAX_VAL 750

int	main(int, char **)
{
	Array<int>	numbers(MAX_VAL);
	int			*mirror = new int[MAX_VAL];

	std::srand(std::time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int	value = std::rand();

		numbers[i] = value;
		mirror[i] = value;
	}
	{
		Array<int>	tmp = numbers;
		Array<int>	test(tmp);

		(void)test;
	}
	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "didn't save the same value!!" << std::endl;
			delete [] mirror;
			return (1);
		}
	}
	try
	{
		numbers[-2] = 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		numbers[MAX_VAL] = 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	for (int i = 0; i < MAX_VAL; i++)
		numbers[i] = std::rand();

	Array<std::string>	words(2);
	words[0] = "deep";
	words[1] = "copy";
	Array<std::string>	copy(words);
	words[0] = "changed";
	std::cout << copy[0] << " " << copy[1] << std::endl;
	std::cout << "size: " << copy.size() << std::endl;

	delete [] mirror;
	return (0);
}
