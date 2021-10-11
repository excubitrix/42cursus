#ifndef CENTRALBUREAUCRACY_H
# define CENTRALBUREAUCRACY_H

# include <iostream>
# include "OfficeBlock.hpp"

class	CentralBureaucracy {

	public:

		CentralBureaucracy(void);
		CentralBureaucracy(CentralBureaucracy const& src);
		virtual ~CentralBureaucracy(void);

		CentralBureaucracy&	operator=(CentralBureaucracy const& src);

		class NoSeatsLeftException : public std::exception {
			virtual const char*	what() const throw();
		};

		class NoTargetException : public std::exception {
			virtual const char*	what() const throw();
		};

		void	hire(Bureaucrat* applicant);
		void	queueUp(std::string const& name);
		void	doBureaucracy(void);

	private:

		static std::string const	_form[4];

		typedef struct	s_queue
		{
			std::string		target;
			struct s_queue	*next;
		}				t_queue;

		t_queue*		_queue;

		Intern			_intern[20];
		OfficeBlock		_ob[20];
};

#endif
