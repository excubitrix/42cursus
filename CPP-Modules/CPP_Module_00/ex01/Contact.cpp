#include "Contact.hpp"

std::string const	Contact::_field[11] = {
	"first name",
	"last name",
	"nickname",
	"login",
	"postal address",
	"email address",
	"phone number",
	"birthday date",
	"favorite meal",
	"underwear color",
	"darkest secret"
};

Contact::Contact(void) {
	std::cout << "Contact default constructor called" << std::endl;
	_first_name = std::string();
	_last_name = std::string();
	_nickname = std::string();
	_login = std::string();
	_postal_address = std::string();
	_email_address = std::string();
	_phone_number = std::string();
	_birthday_date = std::string();
	_favorite_meal = std::string();
	_underwear_color = std::string();
	_darkest_secret = std::string();
	return ;
}

Contact::~Contact(void) {
	std::cout << "Contact destructor called" << std::endl;
	return ;
}

std::string	Contact::get_field(int index) const {
	if (index >= 0 && index < 11)
		return this->_field[index];
	std::cout << RED "Error: Invalid index" RESET << std::endl;
	return (NULL);
}

std::string	Contact::get_attribute(std::string field) const {
	if (field.compare("first name") == 0)
		return this->_first_name;
	else if (field.compare("last name") == 0)
		return this->_last_name;
	else if (field.compare("nickname") == 0)
		return this->_nickname;
	else if (field.compare("login") == 0)
		return this->_login;
	else if (field.compare("postal address") == 0)
		return this->_postal_address;
	else if (field.compare("email address") == 0)
		return this->_email_address;
	else if (field.compare("phone number") == 0)
		return this->_phone_number;
	else if (field.compare("birthday date") == 0)
		return this->_birthday_date;
	else if (field.compare("favorite meal") == 0)
		return this->_favorite_meal;
	else if (field.compare("underwear color") == 0)
		return this->_underwear_color;
	else if (field.compare("darkest secret") == 0)
		return this->_darkest_secret;
	std::cout << RED "Error: There is no such field." RESET << std::endl;
	return NULL;
}

bool	Contact::set_attribute(std::string field, std::string new_value) {
	if (field.compare("first name") == 0)
		_first_name = new_value;
	else if (field.compare("last name") == 0)
		_last_name = new_value;
	else if (field.compare("nickname") == 0)
		_nickname = new_value;
	else if (field.compare("login") == 0)
		_login = new_value;
	else if (field.compare("postal address") == 0)
		_postal_address = new_value;
	else if (field.compare("email address") == 0)
		_email_address = new_value;
	else if (field.compare("phone number") == 0)
		_phone_number = new_value;
	else if (field.compare("birthday date") == 0)
		_birthday_date = new_value;
	else if (field.compare("favorite meal") == 0)
		_favorite_meal = new_value;
	else if (field.compare("underwear color") == 0)
		_underwear_color = new_value;
	else if (field.compare("darkest secret") == 0)
		_darkest_secret = new_value;
	else
	{
		std::cout << RED "Error: There is no such field." RESET << std::endl;
		return (false);
	}
	return (true);
}

void	Contact::view_contact(void) const {
	std::cout << "---------------------------------------------" << std::endl
			  << "|" << std::setw(31) << "Contact Information:"  << std::setw(13) << "|" << std::endl
			  << "---------------------------------------------" << std::endl;
	for (int i = 0; i < 11; i++)
		std::cout << std::setw(15) << this->get_field(i)
				  << ": " + this->get_attribute(this->get_field(i))
				  << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
}
