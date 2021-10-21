#ifndef VICTIM_H
# define VICTIM_H

# include <iostream>

class	Victim {

	public:

		Victim(std::string name);
		Victim(Victim const& src);
		virtual ~Victim(void);

		Victim&	operator=(Victim const& src);

		std::string	getName(void) const;

		virtual void	getPolymorphed(void) const;

	protected:

		std::string	_name;

	private:

		Victim(void);
};

std::ostream&	operator<<(std::ostream& out, Victim const& src);

#endif
