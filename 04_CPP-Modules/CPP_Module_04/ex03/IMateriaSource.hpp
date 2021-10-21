#ifndef IMATERIASOURCE_H
# define IMATERIASOURCE_H

class	AMateria;

class	IMateriaSource {

	public:

		virtual	~IMateriaSource() {}

		virtual void		learnMateria(AMateria* m) = 0;
		virtual AMateria*	createMateria(std::string const & type) = 0;
};

#endif
