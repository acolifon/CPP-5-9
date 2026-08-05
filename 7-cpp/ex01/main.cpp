#include "iter.hpp"
#include <iostream>
#include <string>

template <typename T>
void	printValue(const T &value)
{
	std::cout << value << std::endl;
}

template <typename T>
void	incrementValue(T &value)
{
	++value;
}

int	main(void)
{
	int			numbers[] = {1, 2, 3, 4};
	std::string	words[] = {"hello", "template", "world"};
	const int	constNumbers[] = {42, 43, 44};

	iter(numbers, 4, incrementValue<int>);
	iter(numbers, 4, printValue<int>);
	iter(words, 3, printValue<std::string>);
	iter(constNumbers, 3, printValue<int>);
	return (0);
}
