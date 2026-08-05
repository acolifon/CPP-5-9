#include "PmergeMe.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdexcept>

static void	printValues(const std::string &label, const std::vector<int> &values)
{
	std::cout << label;
	for (std::size_t i = 0; i < values.size(); ++i)
		std::cout << " " << values[i];
	std::cout << std::endl;
}

static double	elapsedMicroseconds(clock_t start, clock_t end)
{
	return (static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC);
}

int	main(int argc, char **argv)
{
	std::vector<int>	display;
	std::vector<int>	vectorValues;
	std::list<int>	listValues;
	clock_t			vectorStart;
	clock_t			listStart;
	clock_t			vectorEnd;
	clock_t			listEnd;

	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	try
	{
		display = PmergeMe::parseVector(argc, argv);
		printValues("Before:", display);

		vectorStart = std::clock();
		vectorValues = PmergeMe::parseVector(argc, argv);
		PmergeMe::sortVector(vectorValues);
		vectorEnd = std::clock();

		listStart = std::clock();
		listValues = PmergeMe::parseList(argc, argv);
		PmergeMe::sortList(listValues);
		listEnd = std::clock();

		printValues("After:", vectorValues);
		std::cout << std::fixed << std::setprecision(5);
		std::cout << "Time to process a range of " << vectorValues.size()
			<< " elements with std::vector : "
			<< elapsedMicroseconds(vectorStart, vectorEnd) << " us" << std::endl;
		std::cout << "Time to process a range of " << listValues.size()
			<< " elements with std::list : "
			<< elapsedMicroseconds(listStart, listEnd) << " us" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
