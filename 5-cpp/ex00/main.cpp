#include "Bureaucrat.hpp"

static void	tryCreate(const std::string &name, int grade)
{
	try
	{
		Bureaucrat	bureaucrat(name, grade);

		std::cout << bureaucrat << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << name << ": " << e.what() << std::endl;
	}
}

int	main(void)
{
	Bureaucrat	arthur("Arthur", 42);

	std::cout << arthur << std::endl;
	arthur.incrementGrade();
	std::cout << arthur << std::endl;
	arthur.decrementGrade();
	std::cout << arthur << std::endl;

	tryCreate("Too high", 0);
	tryCreate("Too low", 151);

	try
	{
		Bureaucrat	boss("Boss", 1);

		boss.incrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Boss: " << e.what() << std::endl;
	}
	return (0);
}
