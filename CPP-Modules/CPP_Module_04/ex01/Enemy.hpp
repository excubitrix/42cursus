#ifndef ENEMY_H
# define ENEMY_H

# include <iostream>

class	Enemy {

	public:

		Enemy(int hp, std::string const& type);
		Enemy(Enemy const& src);
		virtual ~Enemy(void);

		Enemy&	operator=(Enemy const& src);

		std::string	getType(void) const;

		int		getHP(void) const;

		virtual void	takeDamage(int amount);

	protected:

		std::string	_type;

		int		_hp;

	private:

		Enemy(void);
};

#endif
