#ifndef RPN_HPP
# define RPN_HPP

# include <string>

class RPN
{
private:
	RPN(void);
	RPN(const RPN &other);
	~RPN(void);

	RPN	&operator=(const RPN &other);

public:
	static int	evaluate(const std::string &expression);
};

#endif
