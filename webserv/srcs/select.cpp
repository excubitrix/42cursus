#include "webserv.hpp"

server&	select_server(webserv& webserv, std::string client_ip, std::string host, int sd)
{
	std::vector<int> servers;
	for (size_t i = 0; i < webserv.servers.size(); i++)
		for (size_t j = 0; j < webserv.servers[i].host.size(); j++)
			if ((client_ip == webserv.servers[i].host[j]
				|| webserv.servers[i].host[j] == "0.0.0.0")
				&& webserv.port_map[sd] == webserv.servers[i].port[j])
				servers.push_back(i);
	std::vector<int>::iterator it;
	host = host.substr(0, host.find(":"));
	for (it = servers.begin(); it != servers.end(); it++)
		for (size_t i = 0; i < webserv.servers[*it].names.size(); i++)
			if (host == webserv.servers[*it].names[i])
				return webserv.servers[*it];
	for (it = servers.begin(); it != servers.end(); it++)
		if (webserv.servers[*it].default_server)
			return webserv.servers[*it];
	throw std::string("500 Internal Server Error");
}

location&	select_location(server server, std::string URI)
{
	// std::cout << URI << '\n'; // TESTING
	if (URI[URI.length() - 1] != '/')
		URI += "/";
	while (!URI.empty())
	{
		for (size_t i = 0; i < server.locations.size(); i++)
			if (server.locations[i].name == URI)
				return server.locations[i];
		URI = URI.substr(0, URI.rfind('/'));
		for (size_t i = 0; i < server.locations.size(); i++)
			if (server.locations[i].name == URI)
				return server.locations[i];
		URI = URI.substr(0, URI.rfind('/') + 1);
	}
	throw std::string("500 Internal Server Error");
}

bool	select_index(request& request)
{
	std::string target(request.headers_map["target"]);
	for (size_t i = 0; i < request.location.index.size(); i++)
	{
		std::string tmp;
		if (target[target.length() - 1] != '/')
			tmp = target + "/" + request.location.index[i];
		else
			tmp = target + request.location.index[i];
		struct stat buffer;
		if (!stat((request.location.root + tmp).c_str(), &buffer))
		{
			request.headers_map["target"] = tmp;
			// std::cout << "new target: " << request.headers_map["target"] << '\n'; // TESTING
			return true;
		}
	}
	return false;
}

void	check_for_cgi(request& request)
{
	std::string target = request.headers_map["target"];
	if (target.rfind(".") != std::string::npos)
	{
		std::string ext = target.substr(target.rfind("."));
		// std::cout << ext << '\n'; // TESTING
		for (size_t i = 0; i < request.server.locations.size(); i++)
		{
			if (request.server.locations[i].name == "*" + ext)
			{
				std::string root = request.location.root;
				request.location = request.server.locations[i];
				request.location.root = root;
				request.location.server = &request.server;
				// std::cout << "location: '" << request.location.name << "'\n"; // TESTING
			}
		}
	}
}
