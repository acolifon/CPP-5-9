#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <iostream>

static AForm	*createShrubbery(const std::string &target)
{
	return (new ShrubberyCreationForm(target));
}

static AForm	*createRobotomy(const std::string &target)
{
	return (new RobotomyRequestForm(target));
}

static AForm	*createPresidential(const std::string &target)
{
	return (new PresidentialPardonForm(target));
}

Intern::Intern(void)
{
}

Intern::Intern(const Intern &other)
{
	(void)other;
}

Intern::~Intern(void)
{
}

Intern	&Intern::operator=(const Intern &other)
{
	(void)other;
	return (*this);
}

AForm	*Intern::makeForm(const std::string &formName, const std::string &target) const
{
	const std::string	names[] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	FormCreator	creators[] = {
		createShrubbery,
		createRobotomy,
		createPresidential
	};

	for (int i = 0; i < 3; ++i)
	{
		if (formName == names[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (creators[i](target));
		}
	}
	std::cout << "Intern couldn't create " << formName << ": unknown form." << std::endl;
	return (0);
}
