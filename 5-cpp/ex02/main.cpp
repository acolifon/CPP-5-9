#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <cstdlib>
#include <ctime>

int	main(void)
{
	std::srand(std::time(NULL));

	Bureaucrat				boss("Boss", 1);
	Bureaucrat				clerk("Clerk", 140);
	ShrubberyCreationForm	shrubbery("home");
	RobotomyRequestForm		robotomy("Bender");
	PresidentialPardonForm	pardon("Arthur Dent");

	std::cout << shrubbery << std::endl;
	clerk.executeForm(shrubbery);
	clerk.signForm(shrubbery);
	clerk.executeForm(shrubbery);

	clerk.signForm(robotomy);
	boss.signForm(robotomy);
	clerk.executeForm(robotomy);
	boss.executeForm(robotomy);

	boss.signForm(pardon);
	clerk.executeForm(pardon);
	boss.executeForm(pardon);
	return (0);
}
