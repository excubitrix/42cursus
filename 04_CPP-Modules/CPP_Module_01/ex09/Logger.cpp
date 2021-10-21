#include "Logger.hpp"

std::string const	Logger::_dest[2] = {
	"console",
	"file"
};

Logger::functionPtr	Logger::_f[2] = {
	&Logger::_logToConsole,
	&Logger::_logToFile
};

Logger::Logger(std::string file) : _file(file) {
	std::cout << "Logger parameter constructor called" << std::endl;
}

Logger::~Logger(void) {
	std::cout << "Logger destructor called" << std::endl;
}

void	Logger::log(std::string const & dest, std::string const & message) {
	for (int i = 0; i < 2; i++)
		if (dest == this->_dest[i])
			(this->*_f[i])(Logger::_makeLogEntry(message));
}

void	Logger::_logToConsole(std::string const entry) const {
	std::cout << entry << std::endl;
}

void	Logger::_logToFile(std::string const entry) const {
	std::ofstream out;
	out.open(this->_file, std::ios_base::app);
	if (!out.good())
	{
		std::cout << RED "Error: Failed to open the file." RESET << std::endl;
		return ;
	}
	out << entry << std::endl;
	out.close();
}

std::string const	Logger::_getTimestamp(void) {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(now);
	tm utc_tm = *localtime(&time);
	std::ostringstream	timestamp;
	timestamp << std::setfill('0') << "["
			  << (1900 + utc_tm.tm_year)
			  << std::setw(2) << utc_tm.tm_mon
			  << std::setw(2) << utc_tm.tm_mday << "_"
			  << std::setw(2) << utc_tm.tm_hour
			  << std::setw(2) << utc_tm.tm_min
			  << std::setw(2) << utc_tm.tm_sec << "] ";
	return timestamp.str();
}

std::string const	Logger::_makeLogEntry(std::string message) {
	return Logger::_getTimestamp() + message;
}
