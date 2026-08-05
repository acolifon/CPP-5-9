#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>

class ScalarConverter
{
private:
	ScalarConverter(void);
	ScalarConverter(const ScalarConverter &other);
	~ScalarConverter(void);

	ScalarConverter	&operator=(const ScalarConverter &other);

public:
	static void	convert(const std::string &literal);
};

#endif
