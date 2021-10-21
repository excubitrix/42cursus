#include "CentralBureaucracy.hpp"

std::string const	CentralBureaucracy::_form[4] = {
	"Shrubbery Creation",
	"Robotomy Request",
	"Presidential Pardon",
	"Mutant Pig Termination"
};

CentralBureaucracy::CentralBureaucracy(void) : _queue(NULL) {
	for (int i = 0; i < 20; i++)
		this->_ob[i].setIntern(this->_intern[i]);
}

CentralBureaucracy::~CentralBureaucracy(void) {
	while (this->_queue)
	{
		t_queue* tmp = this->_queue->next;
		delete this->_queue;
		this->_queue = tmp;
	}
}

const char*	CentralBureaucracy::NoSeatsLeftException::what() const throw() {
	return RED "All positions have been filled" RESET;
}

const char*	CentralBureaucracy::NoTargetException::what() const throw() {
	return RED "No target" RESET;
}

void	CentralBureaucracy::hire(Bureaucrat* applicant) {
	for (int i = 0; i < 20; i++)
	{
		if (!this->_ob[i].getSigner())
		{
			this->_ob[i].setSigner(*applicant);
			return ;
		}
		else if (!this->_ob[i].getExecutor())
		{
			this->_ob[i].setExecutor(*applicant);
			return ;
		}
	}
	std::cout << HONEY << "Bureaucrat " << applicant << RESET << " was " << RED
			  << "rejected" << RESET << " because: ";
	throw NoSeatsLeftException();
}

void	CentralBureaucracy::queueUp(std::string const& name) {
	if (!this->_queue)
	{
		this->_queue = new t_queue;
		this->_queue->target = name;
		this->_queue->next = NULL;
	}
	else
	{
		t_queue* tmp = this->_queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new t_queue;
		tmp->next->target = name;
		tmp->next->next = NULL;
	}
}

void	CentralBureaucracy::doBureaucracy(void) {
	if (!this->_queue)
		throw NoTargetException();
	while (this->_queue)
	{
		for (int i = 0; i < 20; i++)
		{
			try
			{
				this->_ob[i].doBureaucracy(this->_form[rand() % 4], this->_queue->target);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		t_queue* tmp = this->_queue->next;
		delete this->_queue;
		this->_queue = tmp;
	}
}
