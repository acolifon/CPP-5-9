#include "Span.hpp"
#include <iostream>
#include <vector>

int	main(void)
{
	Span	sp(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	try
	{
		sp.addNumber(42);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::vector<int>	values;
	for (int i = 0; i < 10000; ++i)
		values.push_back(i * 2);

	Span	big(values.size());
	big.addRange(values.begin(), values.end());
	std::cout << big.shortestSpan() << std::endl;
	std::cout << big.longestSpan() << std::endl;
	return (0);
}
