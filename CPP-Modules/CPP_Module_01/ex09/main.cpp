#include "Logger.hpp"

int		main(void)
{
	Logger	logger("test.log");

	logger.log("console", "testing 1");
	logger.log("file", "testing 2");
	
	return 0;
}
