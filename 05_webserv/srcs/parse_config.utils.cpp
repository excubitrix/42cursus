#include "webserv.hpp"

/********************************************************************/
/* ----------------------- HELPER FUNCTIONS ----------------------- */

size_t	skip_space(std::string const& str, size_t start)
{
	for (size_t pos = start; pos < str.size(); pos++)
	{
		pos = str.find_first_not_of(" \n\t\v\f\r", pos);
		if (pos != std::string::npos && str[pos] == '#')
		{
			pos = str.find("\n", pos);
			if (pos == std::string::npos)
				return pos;
		}
		else
			return pos;
	}
	return std::string::npos;
}

size_t	find_brace(std::string const& str, size_t start)
{
	for (size_t pos = start; pos < str.size(); pos++)
	{
		pos = skip_space(str, pos);
		if (pos != std::string::npos && str[pos] != '{' && str[pos] != '}')
			continue ;
		return pos;
	}
	return std::string::npos;
}

std::vector<std::string>	get_params(std::string const& params)
{
	std::istringstream ss(params);
	std::vector<std::string> values;
	std::string tmp;
	while (ss >> tmp)
		values.push_back(tmp);
	return values;
}

void	add_default_location(server& server)
{
	location location(server);
	location.name = "/";
	edit_location(server, location);
	server.locations.push_back(location);
}

void	check_server_names(webserv& webserv, server& server, std::string host_port)
{
	static std::map<std::string, std::vector<std::string> > save;
	std::vector<std::string> names = save[host_port];
	for (size_t i = 0; i < server.names.size(); i++)
	{
		for (size_t j = 0; j < names.size(); j++)
		{
			if (server.names[i] == names[j])
			{
				if (webserv.ignore_warnings)
					std::cerr << "Warning: conflicting server name '" << server.names[i]
							  << "' on " << host_port << ", ignored\n";
				else
					throw std::runtime_error("warning: conflicting server name '"
						+ server.names[i] + "' on " + host_port);
			}
		}
		names.push_back(server.names[i]);
	}
	save[host_port] = names;
}

std::string	extract_server_block(std::string const& str, size_t& pos, size_t& tmp)
{
	int openBrace = 0;
	if ((pos = find_brace(str, tmp)) == std::string::npos || str[pos] != '{')
		throw std::runtime_error("server: expected a '{'");
	if (str[++pos] == '}')
		throw std::runtime_error("server: missing body");
	if ((tmp = find_brace(str, pos)) == std::string::npos)
		throw std::runtime_error("server: expected a '}'");
	while (str[tmp] == '{')
	{
		openBrace++;
		if ((tmp = find_brace(str, ++tmp)) == std::string::npos)
			throw std::runtime_error("server: expected a '}'");
		while (openBrace && str[tmp] == '}')
		{
			openBrace--;
			if ((tmp = find_brace(str, ++tmp)) == std::string::npos)
				throw std::runtime_error("server: expected a '}'");
		}
	}
	return str.substr(pos + 1, tmp - pos - 1);
}

std::string	extract_location_block(std::string const& str, size_t& pos, size_t& tmp)
{
	if ((pos = skip_space(str, tmp)) == std::string::npos)
		throw std::runtime_error("location: unexpected end of file");
	if (str[pos] == '{')
		throw std::runtime_error("location: missing prefix");
	if ((tmp = find_brace(str, pos)) == std::string::npos || str[tmp] != '{')
		throw std::runtime_error("location: expected a '{'");
	if (tmp + 1 >= str.size())
		throw std::runtime_error("location: expected a '}'");
	if (str[++tmp] == '}')
		throw std::runtime_error("location: missing body");
	if ((tmp = find_brace(str, tmp)) == std::string::npos || str[tmp] != '}')
		throw std::runtime_error("location: expected a '}'");
	std::string location = str.substr(pos, tmp - pos - 1);
	pos = tmp;
	return location;
}
