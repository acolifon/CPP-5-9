#include "Bureaucrat.hpp"
#include "Form.hpp"

static void	tryCreateForm(const std::string &name, int signGrade, int executeGrade)
{
	try
	{
		Form	form(name, signGrade, executeGrade);

		std::cout << form << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << name << ": " << e.what() << std::endl;
	}
}

int	main(void)
{
	Bureaucrat	boss("Boss", 1);
	Bureaucrat	clerk("Clerk", 140);
	Form		taxes("Tax Form", 50, 25);

	std::cout << boss << std::endl;
	std::cout << clerk << std::endl;
	std::cout << taxes << std::endl;

	clerk.signForm(taxes);
	boss.signForm(taxes);
	std::cout << taxes << std::endl;

	tryCreateForm("Too hard", 0, 42);
	tryCreateForm("Too easy", 42, 151);
	return (0);
}
