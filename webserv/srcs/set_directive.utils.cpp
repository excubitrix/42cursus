#include "webserv.hpp"

/********************************************************************/
/* ------------------- STATIC GLOBAL VARIABLES -------------------- */

/* Source: https://chromium.googlesource.com/chromium/src.git/+/refs/heads/main/net/base/port_util.cc */
static size_t const	restricted_ports[17] = {
	1719,
	1720,
	1723,
	2049,
	3659,
	4045,
	5060,
	5061,
	6000,
	6566,
	6665,
	6666,
	6667,
	6668,
	6669,
	6697,
	10080
};

/********************************************************************/
/* ----------------------- HELPER FUNCTIONS ----------------------- */

size_t	param_to_u_int(std::string const& value)
{
	size_t tmp;
	std::istringstream iss(value);
	if (!(iss >> tmp) || tmp < 0)
		throw std::runtime_error("param_to_u_int: parsing error");
	return tmp;
}

std::string conform_path(std::string const& param, bool trailing_slash)
{
	std::string tmp(param);
	if (tmp.substr(0, 2) == "./")
		tmp.replace(0, 2, "");
	if (trailing_slash && tmp[tmp.length() - 1] != '/')
		tmp.append("/");
	if (!trailing_slash && tmp[tmp.length() - 1] == '/')
		tmp = tmp.substr(0, tmp.length() - 1);
	return tmp;
}

void	check_port(server const& server, size_t const& new_port)
{
	if (new_port < 1024 || new_port > 49151)
		throw std::runtime_error(SSTR("listen: port '"
			<< new_port << "' falls out of range"));
	for (size_t i = 0; i < 17; i++)
		if (new_port == restricted_ports[i])
			throw std::runtime_error(SSTR("listen: port '"
				<< new_port << "' is blocked"));
	for (size_t i = 0; i < server.port.size(); i++)
		if (new_port == server.port[i])
			throw std::runtime_error(SSTR("listen: duplicate port '"
				<< new_port << "'"));
}

bool	is_ip(std::string str)
{
	if (str.find_first_not_of("0123456789.") != std::string::npos)
		return false;
	size_t pos = 0;
	size_t count = 0;
	while ((pos = str.find(".")) != std::string::npos)
	{
		if (++count > 3)
			return false;
		size_t num = param_to_u_int(str.substr(0, pos));
		if (num < 0 || num > 255)
			return false;
		str.erase(0, pos + 1);
	}
	return true;
}
