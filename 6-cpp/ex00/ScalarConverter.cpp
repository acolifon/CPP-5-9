#include "ScalarConverter.hpp"
#include <cerrno>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

ScalarConverter::ScalarConverter(void)
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	(void)other;
}

ScalarConverter::~ScalarConverter(void)
{
}

ScalarConverter	&ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return (*this);
}

static bool	isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	isNan(double value)
{
	return (value != value);
}

static bool	isInf(double value)
{
	return (value == std::numeric_limits<double>::infinity()
		|| value == -std::numeric_limits<double>::infinity());
}

static bool	isFinite(double value)
{
	return (!isNan(value) && !isInf(value));
}

static bool	parseLiteral(const std::string &literal, double &value)
{
	char	*end;

	if (literal.length() == 1 && !isDigit(literal[0]))
	{
		value = static_cast<double>(literal[0]);
		return (true);
	}
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
	{
		value = static_cast<double>(literal[1]);
		return (true);
	}
	errno = 0;
	value = std::strtod(literal.c_str(), &end);
	if (end == literal.c_str())
		return (false);
	if (*end == '\0')
		return (errno != ERANGE || isInf(value));
	if (*end == 'f' && *(end + 1) == '\0')
		return (errno != ERANGE || isInf(value));
	return (false);
}

static void	printChar(double value)
{
	if (!isFinite(value) || value < 0 || value > 127)
	{
		std::cout << "char: impossible" << std::endl;
		return ;
	}
	char	c = static_cast<char>(value);
	if (c < 32 || c > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << c << "'" << std::endl;
}

static void	printInt(double value)
{
	if (!isFinite(value) || value < static_cast<double>(INT_MIN)
		|| value > static_cast<double>(INT_MAX))
	{
		std::cout << "int: impossible" << std::endl;
		return ;
	}
	std::cout << "int: " << static_cast<int>(value) << std::endl;
}

static bool	hasNoFraction(double value)
{
	return (isFinite(value) && std::floor(value) == value);
}

static void	printFloat(double value)
{
	float	floatValue;

	if (isFinite(value)
		&& (value > static_cast<double>(std::numeric_limits<float>::max())
			|| value < -static_cast<double>(std::numeric_limits<float>::max())))
	{
		std::cout << "float: impossible" << std::endl;
		return ;
	}
	floatValue = static_cast<float>(value);
	std::cout << "float: ";
	if (hasNoFraction(value))
		std::cout << std::fixed << std::setprecision(1) << floatValue;
	else
		std::cout << floatValue;
	std::cout << "f" << std::endl;
	std::cout.unsetf(std::ios::floatfield);
	std::cout << std::setprecision(6);
}

static void	printDouble(double value)
{
	std::cout << "double: ";
	if (hasNoFraction(value))
		std::cout << std::fixed << std::setprecision(1) << value;
	else
		std::cout << value;
	std::cout << std::endl;
	std::cout.unsetf(std::ios::floatfield);
	std::cout << std::setprecision(6);
}

void	ScalarConverter::convert(const std::string &literal)
{
	double	value;

	if (!parseLiteral(literal, value))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return ;
	}
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}
