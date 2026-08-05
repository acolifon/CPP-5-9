#include "Span.hpp"

Span::Span(void) : _capacity(0), _numbers()
{
}

Span::Span(unsigned int capacity) : _capacity(capacity), _numbers()
{
}

Span::Span(const Span &other) : _capacity(other._capacity), _numbers(other._numbers)
{
}

Span::~Span(void)
{
}

Span	&Span::operator=(const Span &other)
{
	if (this != &other)
	{
		_capacity = other._capacity;
		_numbers = other._numbers;
	}
	return (*this);
}

void	Span::addNumber(int number)
{
	if (_numbers.size() >= _capacity)
		throw std::runtime_error("span is full");
	_numbers.push_back(number);
}

unsigned int	Span::shortestSpan(void) const
{
	std::vector<int>	copy;
	unsigned long	best;

	if (_numbers.size() < 2)
		throw std::runtime_error("not enough numbers");
	copy = _numbers;
	std::sort(copy.begin(), copy.end());
	best = ULONG_MAX;
	for (std::size_t i = 1; i < copy.size(); ++i)
	{
		unsigned long	diff = static_cast<unsigned long>(
			static_cast<long>(copy[i]) - static_cast<long>(copy[i - 1]));
		if (diff < best)
			best = diff;
	}
	return (static_cast<unsigned int>(best));
}

unsigned int	Span::longestSpan(void) const
{
	std::vector<int>::const_iterator	minIt;
	std::vector<int>::const_iterator	maxIt;
	unsigned long					diff;

	if (_numbers.size() < 2)
		throw std::runtime_error("not enough numbers");
	minIt = std::min_element(_numbers.begin(), _numbers.end());
	maxIt = std::max_element(_numbers.begin(), _numbers.end());
	diff = static_cast<unsigned long>(static_cast<long>(*maxIt) - static_cast<long>(*minIt));
	return (static_cast<unsigned int>(diff));
}

unsigned int	Span::size(void) const
{
	return (static_cast<unsigned int>(_numbers.size()));
}

unsigned int	Span::capacity(void) const
{
	return (_capacity);
}
