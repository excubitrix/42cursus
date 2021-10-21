#ifndef CONTACT_H
# define CONTACT_H

# include <iostream>
# include <iomanip>

# define RESET "\033[0m"
# define RED "\033[31m"

class	Contact {

	public:

		Contact(void);
		~Contact(void);

		std::string	get_field(int index) const;
		std::string	get_attribute(std::string field) const;
		bool		set_attribute(std::string field, std::string new_value);
		void		view_contact(void) const;

	private:

		static std::string const	_field[11];

		std::string	_first_name;
		std::string	_last_name;
		std::string	_nickname;
		std::string	_login;
		std::string	_postal_address;
		std::string	_email_address;
		std::string	_phone_number;
		std::string	_birthday_date;
		std::string	_favorite_meal;
		std::string	_underwear_color;
		std::string	_darkest_secret;
};

#endif
