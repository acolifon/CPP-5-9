#include "BitcoinExchange.hpp"
#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

BitcoinExchange::BitcoinExchange(void) : _database()
{
}

BitcoinExchange::BitcoinExchange(const std::string &databasePath) : _database()
{
	loadDatabase(databasePath);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database)
{
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_database = other._database;
	return (*this);
}

static bool	isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

std::string	BitcoinExchange::trim(const std::string &value)
{
	std::size_t	begin = 0;
	std::size_t	end = value.length();

	while (begin < end && (value[begin] == ' ' || value[begin] == '\t'))
		++begin;
	while (end > begin && (value[end - 1] == ' ' || value[end - 1] == '\t'
			|| value[end - 1] == '\r'))
		--end;
	return (value.substr(begin, end - begin));
}

static bool	isLeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

bool	BitcoinExchange::isValidDate(const std::string &date)
{
	int			year;
	int			month;
	int			day;
	const int	daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	for (std::size_t i = 0; i < date.length(); ++i)
	{
		if (i != 4 && i != 7 && !isDigit(date[i]))
			return (false);
	}
	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());
	if (year < 1 || month < 1 || month > 12 || day < 1)
		return (false);
	if (month == 2 && isLeapYear(year))
		return (day <= 29);
	return (day <= daysInMonth[month - 1]);
}

bool	BitcoinExchange::parseNumber(const std::string &text, double &value)
{
	char		*end;
	std::string	trimmed = trim(text);

	if (trimmed.empty())
		return (false);
	errno = 0;
	value = std::strtod(trimmed.c_str(), &end);
	if (end == trimmed.c_str() || *end != '\0' || errno == ERANGE)
		return (false);
	if (value != value || value == std::numeric_limits<double>::infinity()
		|| value == -std::numeric_limits<double>::infinity())
		return (false);
	return (true);
}

BitcoinExchange::ValueStatus	BitcoinExchange::parseInputValue(
	const std::string &text,
	double &value)
{
	if (!parseNumber(text, value))
		return (VALUE_BAD);
	if (value < 0)
		return (VALUE_NEGATIVE);
	if (value > 1000)
		return (VALUE_TOO_LARGE);
	return (VALUE_OK);
}

void	BitcoinExchange::loadDatabaseLine(const std::string &line)
{
	std::size_t	comma;
	std::string	date;
	double		rate;

	if (line.empty() || line == "date,exchange_rate")
		return ;
	comma = line.find(',');
	if (comma == std::string::npos)
		return ;
	date = trim(line.substr(0, comma));
	if (!isValidDate(date) || !parseNumber(line.substr(comma + 1), rate))
		return ;
	_database[date] = rate;
}

void	BitcoinExchange::loadDatabase(const std::string &path)
{
	std::ifstream	file(path.c_str());
	std::string		line;

	if (!file)
		throw std::runtime_error("could not open database.");
	while (std::getline(file, line))
		loadDatabaseLine(line);
	if (_database.empty())
		throw std::runtime_error("database is empty.");
}

bool	BitcoinExchange::getRate(const std::string &date, double &rate) const
{
	std::map<std::string, double>::const_iterator	it = _database.lower_bound(date);

	if (it != _database.end() && it->first == date)
	{
		rate = it->second;
		return (true);
	}
	if (it == _database.begin())
		return (false);
	--it;
	rate = it->second;
	return (true);
}

void	BitcoinExchange::processLine(const std::string &line) const
{
	std::size_t	delimiter;
	std::string	date;
	std::string	valueText;
	double		value;
	double		rate;
	ValueStatus	status;

	if (line.empty() || line == "date | value")
		return ;
	delimiter = line.find(" | ");
	if (delimiter == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return ;
	}
	date = trim(line.substr(0, delimiter));
	valueText = trim(line.substr(delimiter + 3));
	if (!isValidDate(date))
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return ;
	}
	status = parseInputValue(valueText, value);
	if (status == VALUE_BAD)
		std::cout << "Error: bad input => " << line << std::endl;
	else if (status == VALUE_NEGATIVE)
		std::cout << "Error: not a positive number." << std::endl;
	else if (status == VALUE_TOO_LARGE)
		std::cout << "Error: too large a number." << std::endl;
	else if (!getRate(date, rate))
		std::cout << "Error: no exchange rate for " << date << "." << std::endl;
	else
		std::cout << date << " => " << valueText << " = " << value * rate << std::endl;
}

void	BitcoinExchange::processInputFile(const std::string &path) const
{
	std::ifstream	file(path.c_str());
	std::string		line;

	if (!file)
		throw std::runtime_error("could not open file.");
	while (std::getline(file, line))
		processLine(line);
}
