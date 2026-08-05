#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <cstdlib>
#include <ctime>

static void	useForm(Bureaucrat &bureaucrat, AForm *form)
{
	if (!form)
		return ;
	bureaucrat.signForm(*form);
	bureaucrat.executeForm(*form);
	delete form;
}

int	main(void)
{
	std::srand(std::time(NULL));

	Intern		intern;
	Bureaucrat	boss("Boss", 1);
	AForm		*form;

	form = intern.makeForm("robotomy request", "Bender");
	useForm(boss, form);

	form = intern.makeForm("shrubbery creation", "garden");
	useForm(boss, form);

	form = intern.makeForm("presidential pardon", "Arthur Dent");
	useForm(boss, form);

	form = intern.makeForm("coffee request", "desk");
	useForm(boss, form);
	return (0);
}
