#include "Directory.hpp"

int	Directory::_num = 0;

Directory::Directory(void) {
	std::cout << "Directory default constructor called" << std::endl;
	return ;
}

Directory::~Directory(void) {
	std::cout << "Directory destructor called" << std::endl;
	return ;
}

bool	Directory::add_contact(void) {
	std::string	input;

	if (this->_num == LIMIT)
		std::cout << "~ " RED "Contact limit reached!\n" RESET
				  << "~ Want to store more contacts? Upgrade to " MAGENTA "DIRECTORY PRO"
				  << RESET " now and get 30% OFF our annual plan!"
				  << std::endl;
	else
	{
		for (int i = 0; i < 11; i++)
		{
			std::cout << "~ Please enter the " YELLOW + this->_contact[this->_num].get_field(i)
					  + RESET " of the contact: ";
			if (!std::getline(std::cin, input))
				return (false);
			while (i < 2 && !input.length())
			{
				std::cout << "~ A " YELLOW "first" RESET " and a " YELLOW "last name"
						  << RESET " are " RED "required." RESET << std::endl
						  << "~ Please enter the " YELLOW + this->_contact[this->_num].get_field(i)
						  + RESET " of the contact: ";
				if (!std::getline(std::cin, input))
					return (false);
			}
			this->_contact[this->_num].set_attribute(this->_contact[0].get_field(i), input);
		}
		std::cout << "~ " GREEN "Contact saved." RESET << std::endl;
		this->_num++;
	}
	return (true);
}

std::string	Directory::_truncate(std::string str, size_t width) {
	if (str.length() > width)
		return str.substr(0, width - 1) + ".";
	return str;
}

void	Directory::display_contacts(void) {
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "|" << std::setw(10) << "Index" << "|"
			  << std::setw(10) << "First Name" << "|"
			  << std::setw(10) << "Last Name" << "|"
			  << std::setw(10) << "Nickname" << "|"
			  << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	for (int i = 0; i < this->_num; i++)
	{
		std::cout << "|" << std::setw(10) << i << "|"
				  << std::setw(10) << _truncate(this->_contact[i].get_attribute("first name"), 10) << "|"
				  << std::setw(10) << _truncate(this->_contact[i].get_attribute("last name"), 10) << "|"
				  << std::setw(10) << _truncate(this->_contact[i].get_attribute("nickname"), 10) << "|"
				  << std::endl;
	}
	std::cout << "---------------------------------------------" << std::endl;
}

bool	Directory::search_contact(void) {
	int	index = 0;

	if (!this->_num)
		std::cout << "~ " RED "No contacts listed. " RESET
				  << "Use the " YELLOW "ADD" RESET " command to add a contact."
				  << std::endl;
	else
	{
		this->display_contacts();
		std::cout << "~ Enter the index of the contact you wish to view: ";
		while (!(std::cin >> index) || index < 0 || index >= this->_num)
		{
			if (std::cin.eof())
				return (false);
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "~ " RED "Input received is invalid. " RESET "Try again: ";
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		this->_contact[index].view_contact();
	}
	return (true);
}
