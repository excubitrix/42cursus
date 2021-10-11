#ifndef SQUAD_H
# define SQUAD_H

# include <iostream>
# include "ISquad.hpp"

class	Squad : public ISquad {

	public:

		Squad(void);
		Squad(Squad const& src);
		virtual ~Squad(void);

		Squad&	operator=(Squad const& src);

		int				getCount(void) const;
		ISpaceMarine*	getUnit(int N) const;
		int				push(ISpaceMarine*);

	private :

		typedef struct	s_unit {
			ISpaceMarine*	marine;
			struct s_unit*	next;
		}				t_unit;

		int			_N;
		t_unit*		_unit;	
};

#endif
