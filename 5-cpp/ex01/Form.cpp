#include "Form.hpp"
#include "Bureaucrat.hpp"

static void	checkGrade(int grade)
{
	if (grade < 1)
		throw Form::GradeTooHighException();
	if (grade > 150)
		throw Form::GradeTooLowException();
}

Form::Form(void)
	: _name("default"), _signed(false), _gradeToSign(150), _gradeToExecute(150)
{
}

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute)
	: _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	checkGrade(_gradeToSign);
	checkGrade(_gradeToExecute);
}

Form::Form(const Form &other)
	: _name(other._name),
	_signed(other._signed),
	_gradeToSign(other._gradeToSign),
	_gradeToExecute(other._gradeToExecute)
{
}

Form::~Form(void)
{
}

Form	&Form::operator=(const Form &other)
{
	if (this != &other)
		_signed = other._signed;
	return (*this);
}

const std::string	&Form::getName(void) const
{
	return (_name);
}

bool	Form::isSigned(void) const
{
	return (_signed);
}

int	Form::getGradeToSign(void) const
{
	return (_gradeToSign);
}

int	Form::getGradeToExecute(void) const
{
	return (_gradeToExecute);
}

void	Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw Form::GradeTooLowException();
	_signed = true;
}

const char	*Form::GradeTooHighException::what(void) const throw()
{
	return ("grade is too high");
}

const char	*Form::GradeTooLowException::what(void) const throw()
{
	return ("grade is too low");
}

std::ostream	&operator<<(std::ostream &out, const Form &form)
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
