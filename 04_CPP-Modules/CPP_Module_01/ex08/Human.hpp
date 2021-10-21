#ifndef HUMAN_H
# define HUMAN_H

# include <iostream>

class	Human {

	public:

		typedef	void(Human::*functionPtr)(std::string const & target);

		void	action(std::string const & action_name, std::string const & target);

	private:

		static std::string const	_action_name[3];
		static functionPtr			_f[3];

		void	_meleeAttack(std::string const & target);
		void	_rangedAttack(std::string const & target);
		void	_intimidatingShout(std::string const & target);

};

#endif
