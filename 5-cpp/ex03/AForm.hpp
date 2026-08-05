#ifndef AFORM_HPP
# define AFORM_HPP

# include <exception>
# include <iostream>
# include <string>

class Bureaucrat;

class AForm
{
private:
	const std::string	_name;
	bool				_signed;
	const int			_gradeToSign;
	const int			_gradeToExecute;

protected:
	virtual void	executeAction(void) const = 0;

public:
	AForm(void);
	AForm(const std::string &name, int gradeToSign, int gradeToExecute);
	AForm(const AForm &other);
	virtual ~AForm(void);

	AForm	&operator=(const AForm &other);

	const std::string	&getName(void) const;
	bool				isSigned(void) const;
	int					getGradeToSign(void) const;
	int					getGradeToExecute(void) const;
	void				beSigned(const Bureaucrat &bureaucrat);
	void				execute(const Bureaucrat &executor) const;

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

	class FormNotSignedException : public std::exception
	{
	public:
		virtual const char	*what(void) const throw();
	};
};

std::ostream	&operator<<(std::ostream &out, const AForm &form);

#endif
