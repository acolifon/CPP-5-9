#include "PmergeMe.hpp"
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <stdexcept>

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	(void)other;
}

PmergeMe::~PmergeMe(void)
{
}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other)
{
	(void)other;
	return (*this);
}

int	PmergeMe::parsePositiveInt(const std::string &text)
{
	char	*end;
	long	value;

	if (text.empty())
		throw std::runtime_error("Error");
	value = std::strtol(text.c_str(), &end, 10);
	if (*end != '\0' || value <= 0 || value > INT_MAX)
		throw std::runtime_error("Error");
	return (static_cast<int>(value));
}

std::vector<int>	PmergeMe::parseVector(int argc, char **argv)
{
	std::vector<int>	values;

	for (int i = 1; i < argc; ++i)
		values.push_back(parsePositiveInt(argv[i]));
	return (values);
}

std::list<int>	PmergeMe::parseList(int argc, char **argv)
{
	std::list<int>	values;

	for (int i = 1; i < argc; ++i)
		values.push_back(parsePositiveInt(argv[i]));
	return (values);
}

std::vector<unsigned int>	PmergeMe::buildInsertionOrder(unsigned int size)
{
	std::vector<unsigned int>	order;
	unsigned int				previous;
	unsigned int				current;

	if (size == 0)
		return (order);
	order.push_back(0);
	previous = 1;
	current = 3;
	while (previous < size)
	{
		unsigned int	end = current;
		unsigned int	next = current + 2 * previous;

		if (end > size)
			end = size;
		for (unsigned int index = end; index > previous; --index)
			order.push_back(index - 1);
		previous = current;
		current = next;
	}
	return (order);
}

void	PmergeMe::insertVector(std::vector<int> &chain, int value)
{
	chain.insert(std::upper_bound(chain.begin(), chain.end(), value), value);
}

void	PmergeMe::insertPairVector(std::vector<Pair> &chain, const Pair &value)
{
	std::vector<Pair>::iterator	it = chain.begin();

	while (it != chain.end() && it->large <= value.large)
		++it;
	chain.insert(it, value);
}

void	PmergeMe::insertList(std::list<int> &chain, int value)
{
	chain.insert(std::upper_bound(chain.begin(), chain.end(), value), value);
}

void	PmergeMe::insertPairList(std::list<Pair> &chain, const Pair &value)
{
	std::list<Pair>::iterator	it = chain.begin();

	while (it != chain.end() && it->large <= value.large)
		++it;
	chain.insert(it, value);
}

void	PmergeMe::sortPairsVector(std::vector<Pair> &pairs)
{
	std::vector<Pair>			main;
	std::vector<Pair>			pend;
	std::vector<unsigned int>	order;
	Pair						odd;
	bool						hasOdd = false;

	if (pairs.size() < 2)
		return ;
	for (std::size_t i = 0; i < pairs.size(); i += 2)
	{
		if (i + 1 >= pairs.size())
		{
			odd = pairs[i];
			hasOdd = true;
		}
		else if (pairs[i].large <= pairs[i + 1].large)
		{
			pend.push_back(pairs[i]);
			main.push_back(pairs[i + 1]);
		}
		else
		{
			pend.push_back(pairs[i + 1]);
			main.push_back(pairs[i]);
		}
	}
	sortPairsVector(main);
	order = buildInsertionOrder(static_cast<unsigned int>(pend.size()));
	for (std::size_t i = 0; i < order.size(); ++i)
		insertPairVector(main, pend[order[i]]);
	if (hasOdd)
		insertPairVector(main, odd);
	pairs = main;
}

void	PmergeMe::sortPairsList(std::list<Pair> &pairs)
{
	std::list<Pair>				main;
	std::vector<Pair>			pend;
	std::vector<unsigned int>	order;
	Pair						first;
	Pair						second;
	Pair						odd;
	bool						hasOdd = false;

	if (pairs.size() < 2)
		return ;
	while (!pairs.empty())
	{
		first = pairs.front();
		pairs.pop_front();
		if (pairs.empty())
		{
			odd = first;
			hasOdd = true;
		}
		else
		{
			second = pairs.front();
			pairs.pop_front();
			if (first.large <= second.large)
			{
				pend.push_back(first);
				main.push_back(second);
			}
			else
			{
				pend.push_back(second);
				main.push_back(first);
			}
		}
	}
	sortPairsList(main);
	order = buildInsertionOrder(static_cast<unsigned int>(pend.size()));
	for (std::size_t i = 0; i < order.size(); ++i)
		insertPairList(main, pend[order[i]]);
	if (hasOdd)
		insertPairList(main, odd);
	pairs = main;
}

void	PmergeMe::sortVector(std::vector<int> &values)
{
	std::vector<Pair>			pairs;
	std::vector<int>			pend;
	std::vector<int>			chain;
	std::vector<unsigned int>	order;
	int							odd = 0;
	bool						hasOdd = false;

	if (values.size() < 2)
		return ;
	for (std::size_t i = 0; i < values.size(); i += 2)
	{
		if (i + 1 >= values.size())
		{
			odd = values[i];
			hasOdd = true;
		}
		else
		{
			Pair	pair;

			if (values[i] < values[i + 1])
			{
				pair.small = values[i];
				pair.large = values[i + 1];
			}
			else
			{
				pair.small = values[i + 1];
				pair.large = values[i];
			}
			pairs.push_back(pair);
		}
	}
	sortPairsVector(pairs);
	for (std::size_t i = 0; i < pairs.size(); ++i)
	{
		chain.push_back(pairs[i].large);
		pend.push_back(pairs[i].small);
	}
	order = buildInsertionOrder(static_cast<unsigned int>(pend.size()));
	for (std::size_t i = 0; i < order.size(); ++i)
		insertVector(chain, pend[order[i]]);
	if (hasOdd)
		insertVector(chain, odd);
	values = chain;
}

void	PmergeMe::sortList(std::list<int> &values)
{
	std::list<Pair>				pairs;
	std::vector<int>			pend;
	std::list<int>				chain;
	std::vector<unsigned int>	order;
	int							first;
	int							second;
	int							odd = 0;
	bool						hasOdd = false;

	if (values.size() < 2)
		return ;
	while (!values.empty())
	{
		first = values.front();
		values.pop_front();
		if (values.empty())
		{
			odd = first;
			hasOdd = true;
		}
		else
		{
			Pair	pair;

			second = values.front();
			values.pop_front();
			if (first < second)
			{
				pair.small = first;
				pair.large = second;
			}
			else
			{
				pair.small = second;
				pair.large = first;
			}
			pairs.push_back(pair);
		}
	}
	sortPairsList(pairs);
	for (std::list<Pair>::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		chain.push_back(it->large);
		pend.push_back(it->small);
	}
	order = buildInsertionOrder(static_cast<unsigned int>(pend.size()));
	for (std::size_t i = 0; i < order.size(); ++i)
		insertList(chain, pend[order[i]]);
	if (hasOdd)
		insertList(chain, odd);
	values = chain;
}
