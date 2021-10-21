#include "webserv.hpp"

/********************************************************************/
/* ---------------------- PARSING FUNCTIONS ----------------------- */

/********************************************************************/
/* 																	*/
/********************************************************************/

void	parse_config(webserv& webserv, std::string const& path)
{
	std::ifstream in(path.c_str());
	std::stringstream ss;
	ss << in.rdbuf();
	if (errno)
	{
		if (in)
			in.close();
		throw std::runtime_error(strerror(errno));
	}
	for (size_t pos = 0; pos < ss.str().size(); pos++)
	{
		if ((pos = skip_space(ss.str(), pos)) == std::string::npos)
			break ;
		size_t tmp = ss.str().find_first_of(" \n\t\v\f\r{", pos);
		std::string context = ss.str().substr(pos, tmp - pos);
		if (context == "server")
		{
			std::string server = extract_server_block(ss.str(), pos, tmp);
			parse_server(webserv, server);
			pos = tmp;
		}
		else
			throw std::runtime_error("config: invalid context '" + context + "'");
	}
	in.close();
}

/********************************************************************/
/* Syntax:	server { ... }											*/
/* Default:	-														*/
/* Context:	http													*/
/********************************************************************/

void	parse_server(webserv& webserv, std::string const& str)
{
	server server;
	std::vector<std::string> locations;
	size_t pos = 0;
	if ((pos = skip_space(str, pos)) == std::string::npos)
		throw std::runtime_error("server: missing body");
	pos--;
	while (pos != std::string::npos && str[pos++])
	{
		if ((pos = skip_space(str, pos)) == std::string::npos)
			break ;
		size_t tmp = str.find_first_of(" \n\t\v\f\r{", pos);
		if (tmp == std::string::npos)
			throw std::runtime_error("server: unexpected end of file");
		if (str.substr(pos, tmp - pos) == "location")
		{
			std::string location = extract_location_block(str, pos, tmp);
			locations.push_back(location);
		}
		else
			set_directive(webserv, &server, "server", str, pos, tmp);
	}
	edit_server(webserv, server);
	parse_locations(webserv, server, locations);
	webserv.servers.push_back(server);
}

/********************************************************************/
/* Syntax:	location name { ... }									*/
/* Default:	-														*/
/* Context:	server													*/
/********************************************************************/

void	parse_locations(webserv const& webserv, server& server,
			std::vector<std::string> const& locations)
{
	std::vector<std::string> names;
	std::vector<std::string>::const_iterator it = locations.begin();
	for (; it != locations.end(); it++)
	{
		// std::cout << CYAN "START\n" RESET << *it << YELLOW "\nEND\n" RESET; // TESTING
		location location(server);
		size_t pos = (*it).find_first_of(" \t\v\f\r{");
		location.name = (*it).substr(0, pos);
		for (size_t i = 0; i < server.locations.size(); i++)
			for (size_t j = 0; j < names.size(); j++)
				if (server.locations[i].name == location.name)
					throw std::runtime_error("location: duplicate location");
		names.push_back(location.name);
		if (skip_space(*it, skip_space(*it, ++pos)) == std::string::npos)
			throw std::runtime_error("location: missing body");
		while (pos != std::string::npos && (*it)[pos++])
		{
			if ((pos = skip_space(*it, pos)) == std::string::npos)
				break ;
			size_t tmp = (*it).find_first_of(" \t\v\f\r", pos);
			set_directive(webserv, &location, "location", *it, pos, tmp);
		}
		edit_location(server, location);
		server.locations.push_back(location);
	}
	for (size_t i = 0; i < server.locations.size(); i++)
	{
		if (server.locations[i].name == "/")
			break ;
		else if (i == server.locations.size() - 1)
			add_default_location(server);
	}
	if (!server.locations.size())
		add_default_location(server);
	names.clear();
}

/********************************************************************/
/* ---------------------- EDITING FUNCTIONS ----------------------- */

/********************************************************************/
/*			Any unset directives are set to their default.			*/
/********************************************************************/

void	edit_server(webserv& webserv, server& server)
{
	if (!server.host.size())
	{
		server.host.push_back("0.0.0.0");
		server.port.push_back(8000);
	}
	static std::vector<size_t> ports;
	for (size_t i = 0; i < server.port.size(); i++)
	{
		for (size_t j = 0; j < ports.size(); j++)
			if (server.port[i] == ports[j])
				goto present;
		server.default_server = true;
		ports.push_back(server.port[i]);
	}
	present:
	if (server.names.empty())
		server.names.push_back("");
	for (size_t i = 0; i < server.host.size(); i++)
		check_server_names(webserv, server, SSTR(server.host[i] << ":"
			<< (int)server.port[i]));
	if (server.root.empty())
		server.root = "www";
	if (server.index.empty())
		server.index.push_back("index.html");
	if (server.accepted_methods.empty())
		server.accepted_methods.push_back("GET");
	if (server.client_max_body_size == -1)
		server.client_max_body_size = 1000000;
	std::map<size_t, std::string>::iterator it = server.error_pages.begin();
	for (; it != server.error_pages.end(); it++)
		if (it->second.empty())
			it->second = SSTR(webserv.cwd << ERROR_DIR << it->first
				<< ".html");
	if (server.upload_path.empty())
		server.upload_path = server.root + "/tmp/uploads/";
}

/********************************************************************/
/*			Any unset directives inherit from the server.			*/
/********************************************************************/

void	edit_location(server& server, location& location)
{
	if (!strncmp(location.name.c_str(), "*.", 2) && !location.cgi)
		throw std::runtime_error("no cgi_pass specified for '" +
			location.name + "'");
	if (location.root.empty())
		location.root = server.root;
	if (location.index.empty())
		location.index = server.index;
	if (location.accepted_methods.empty())
		location.accepted_methods = server.accepted_methods;
	if (location.client_max_body_size == -1)
		location.client_max_body_size = server.client_max_body_size;
	std::map<size_t, std::string>::iterator it = location.error_pages.begin();
	for (; it != location.error_pages.end(); it++)
		if (it->second.empty())
			it->second = server.error_pages[it->first];
	if (location.error_pages.empty())
		location.error_pages = server.error_pages;
	if (location.upload_path.empty())
		location.upload_path = server.upload_path;
}
