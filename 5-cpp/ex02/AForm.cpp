#include "AForm.hpp"
#include "Bureaucrat.hpp"

static void	checkGrade(int grade)
{
	if (grade < 1)
		throw AForm::GradeTooHighException();
	if (grade > 150)
		throw AForm::GradeTooLowException();
}

AForm::AForm(void)
	: _name("default"), _signed(false), _gradeToSign(150), _gradeToExecute(150)
{
}

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute)
	: _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	checkGrade(_gradeToSign);
	checkGrade(_gradeToExecute);
}

AForm::AForm(const AForm &other)
	: _name(other._name),
	_signed(other._signed),
	_gradeToSign(other._gradeToSign),
	_gradeToExecute(other._gradeToExecute)
{
}

AForm::~AForm(void)
{
}

AForm	&AForm::operator=(const AForm &other)
{
	if (this != &other)
		_signed = other._signed;
	return (*this);
}

const std::string	&AForm::getName(void) const
{
	return (_name);
}

bool	AForm::isSigned(void) const
{
	return (_signed);
}

int	AForm::getGradeToSign(void) const
{
	return (_gradeToSign);
}

int	AForm::getGradeToExecute(void) const
{
	return (_gradeToExecute);
}

void	AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw AForm::GradeTooLowException();
	_signed = true;
}

void	AForm::execute(const Bureaucrat &executor) const
{
	if (!_signed)
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > _gradeToExecute)
		throw AForm::GradeTooLowException();
	executeAction();
}

const char	*AForm::GradeTooHighException::what(void) const throw()
{
	return ("grade is too high");
}

const char	*AForm::GradeTooLowException::what(void) const throw()
{
	return ("grade is too low");
}

const char	*AForm::FormNotSignedException::what(void) const throw()
{
	return ("form is not signed");
}

std::ostream	&operator<<(std::ostream &out, const AForm &form)
{
	out << form.getName() << " form, signed: ";
	if (form.isSigned())
		out << "yes";
	else
		out << "no";
	out << ", sign grade: " << form.getGradeToSign()
		<< ", execute grade: " << form.getGradeToExecute() << ".";
	return (out);
}
