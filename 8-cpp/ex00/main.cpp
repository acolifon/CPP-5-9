#include "easyfind.hpp"
#include <deque>
#include <iostream>
#include <list>
#include <vector>

template <typename T>
static void	testFind(T &container, int value)
{
	try
	{
		std::cout << "found " << *easyfind(container, value) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << value << ": " << e.what() << std::endl;
	}
}

int	main(void)
{
	std::vector<int>	vector;
	std::list<int>	list;
	std::deque<int>	deque;

	for (int i = 0; i < 5; ++i)
	{
		vector.push_back(i * 2);
		list.push_back(i * 3);
		deque.push_back(i * 4);
	}
	testFind(vector, 4);
	testFind(list, 9);
	testFind(deque, 16);
	testFind(vector, 5);
	return (0);
}
