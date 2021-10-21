#ifndef PONY_H
# define PONY_H

# include <iostream>
# include <iomanip>

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"

class	Pony {

	public:

		Pony(std::string name);
		Pony(void);
		~Pony(void);

		bool	rename(std::string new_name);
		void	eat(void);
		void	sleep(void);
		bool	train(std::string skill, int duration);
		void	display_stats(void) const;

	private:

		std::string	_name;

		float		_engery;
		float		_weight;

		float		_stamina;
		float		_speed;
		float		_dressage;
		float		_gallop;
		float		_trot;
		float		_jumping;

		void	_restore_energy(float amount);
		float	_get_skill(std::string skill) const;
		void	_set_skill(std::string skill, float new_value);
};

#endif
