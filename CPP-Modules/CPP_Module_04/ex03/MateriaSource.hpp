#ifndef MATERIASOURCE_H
# define MATERIASOURCE_H

# include <iostream>
# include "IMateriaSource.hpp"
# include "AMateria.hpp"

class	MateriaSource : public IMateriaSource {

	public:

		MateriaSource(void);
		MateriaSource(MateriaSource const& src);
		virtual ~MateriaSource(void);

		MateriaSource&	operator=(MateriaSource const& src);

		void		learnMateria(AMateria* m);
		AMateria*	createMateria(std::string const& type);

	private:

		AMateria*	_materia[4];
};

#endif
