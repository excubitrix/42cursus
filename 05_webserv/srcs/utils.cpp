#include "webserv.hpp"

bool	is_file(std::string path)
{
	struct stat buffer;
	if (stat(path.c_str(), &buffer) != 0)
		return false;
	return S_ISREG(buffer.st_mode);
}

bool	is_directory(std::string path)
{
	struct stat buffer;
	if (stat(path.c_str(), &buffer) != 0)
		return false;
	return S_ISDIR(buffer.st_mode);
}

std::string	ft_inet_ntoa(struct in_addr in)
{
	std::stringstream ss;

	unsigned char* bytes = (unsigned char*) &in;
	for (int i = 0; i < 4; i++)
	{
		ss << (int)bytes[i];
		if (i != 3)
			ss << '.';
	}
	return ss.str();
}

bool mkdir_p(std::string path)
{
    size_t current_pos = 0;
    size_t dir_end;
    std::string dir;

    while (true)
    {
        /* add directory from path */
        dir_end = path.find('/', current_pos);
        dir = path.substr(0, dir_end);
        
		if (is_directory(dir) == false)
		{
			if (mkdir(dir.c_str(), 0700) == -1)
			{
				perror("error mkdir()");
				return (false);
			}
		}
        
        /* if no next slash was found, we're done */
        if (dir_end == std::string::npos)
            break ;
        
		/* move to start of next directory in path */
        current_pos = dir_end + 1;
    }
	return (true);
}
