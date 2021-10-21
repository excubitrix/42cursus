#ifndef LOGGER_H
# define LOGGER_H

# include <iostream>
# include <iomanip>
# include <sstream>
# include <fstream>
# include <chrono>

# define RESET "\033[0m"
# define RED "\033[31m"

class	Logger {

	public:

		typedef	void(Logger::*functionPtr)(std::string const entry) const;

		Logger(std::string file);
		~Logger(void);

		void	log(std::string const & dest, std::string const & message);
	
	private:

		static std::string const	_dest[2];
		static functionPtr			_f[2];

		std::string const	_file;

		void	_logToConsole(std::string const entry) const;
		void	_logToFile(std::string const entry) const;

		std::string const	_getTimestamp(void);
		std::string const	_makeLogEntry(std::string message);
};

#endif
