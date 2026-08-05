#ifndef SPAN_HPP
# define SPAN_HPP

# include <algorithm>
# include <climits>
# include <iterator>
# include <stdexcept>
# include <vector>

class Span
{
private:
	unsigned int		_capacity;
	std::vector<int>	_numbers;

public:
	Span(void);
	Span(unsigned int capacity);
	Span(const Span &other);
	~Span(void);

	Span	&operator=(const Span &other);

	void			addNumber(int number);
	unsigned int	shortestSpan(void) const;
	unsigned int	longestSpan(void) const;
	unsigned int	size(void) const;
	unsigned int	capacity(void) const;

	template <typename InputIterator>
	void	addRange(InputIterator first, InputIterator last)
	{
		typename std::iterator_traits<InputIterator>::difference_type	count;

		count = std::distance(first, last);
		if (count < 0 || static_cast<unsigned int>(count) > _capacity - _numbers.size())
			throw std::runtime_error("span is full");
		_numbers.insert(_numbers.end(), first, last);
	}
};

#endif
