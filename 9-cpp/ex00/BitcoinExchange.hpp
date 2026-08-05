#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
private:
	std::map<std::string, double>	_database;

	enum ValueStatus
	{
		VALUE_OK,
		VALUE_BAD,
		VALUE_NEGATIVE,
		VALUE_TOO_LARGE
	};

	static std::string	trim(const std::string &value);
	static bool			isValidDate(const std::string &date);
	static bool			parseNumber(const std::string &text, double &value);
	static ValueStatus	parseInputValue(const std::string &text, double &value);
	bool				getRate(const std::string &date, double &rate) const;
	void				loadDatabaseLine(const std::string &line);
	void				processLine(const std::string &line) const;

public:
	BitcoinExchange(void);
	BitcoinExchange(const std::string &databasePath);
	BitcoinExchange(const BitcoinExchange &other);
	~BitcoinExchange(void);

	BitcoinExchange	&operator=(const BitcoinExchange &other);

	void	loadDatabase(const std::string &path);
	void	processInputFile(const std::string &path) const;
};

#endif
