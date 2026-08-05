#ifndef INTERN_HPP
# define INTERN_HPP

# include "AForm.hpp"
# include <string>

class Intern
{
private:
	typedef AForm	*(*FormCreator)(const std::string &target);

public:
	Intern(void);
	Intern(const Intern &other);
	~Intern(void);

	Intern	&operator=(const Intern &other);

	AForm	*makeForm(const std::string &formName, const std::string &target) const;
};

#endif
