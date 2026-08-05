#include "RPN.hpp"
#include <sstream>
#include <stack>
#include <stdexcept>

RPN::RPN(void)
{
}

RPN::RPN(const RPN &other)
{
	(void)other;
}

RPN::~RPN(void)
{
}

RPN	&RPN::operator=(const RPN &other)
{
	(void)other;
	return (*this);
}

static bool	isOperator(const std::string &token)
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

static int	applyOperator(int left, int right, const std::string &token)
{
	if (token == "+")
		return (left + right);
	if (token == "-")
		return (left - right);
	if (token == "*")
		return (left * right);
	if (right == 0)
		throw std::runtime_error("Error");
	return (left / right);
}

int	RPN::evaluate(const std::string &expression)
{
	std::istringstream	stream(expression);
	std::stack<int>		numbers;
	std::string			token;

	while (stream >> token)
	{
		if (token.length() == 1 && token[0] >= '0' && token[0] <= '9')
			numbers.push(token[0] - '0');
		else if (isOperator(token))
		{
			int	right;
			int	left;

			if (numbers.size() < 2)
				throw std::runtime_error("Error");
			right = numbers.top();
			numbers.pop();
			left = numbers.top();
			numbers.pop();
			numbers.push(applyOperator(left, right, token));
		}
		else
			throw std::runtime_error("Error");
	}
	if (numbers.size() != 1)
		throw std::runtime_error("Error");
	return (numbers.top());
}
