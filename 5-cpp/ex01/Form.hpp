#ifndef FORM_HPP
# define FORM_HPP

# include <exception>
# include <iostream>
# include <string>

class Bureaucrat;

class Form
{
private:
	const std::string	_name;
	bool				_signed;
	const int			_gradeToSign;
	const int			_gradeToExecute;

public:
	Form(void);
	Form(const std::string &name, int gradeToSign, int gradeToExecute);
	Form(const Form &other);
	~Form(void);

	Form	&operator=(const Form &other);

	const std::string	&getName(void) const;
	bool				isSigned(void) const;
	int					getGradeToSign(void) const;
	int					getGradeToExecute(void) const;
	void				beSigned(const Bureaucrat &bureaucrat);

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char	*what(void) const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char	*what(void) const throw();
	};
};

std::ostream	&operator<<(std::ostream &out, const Form &form);

#endif
