#include "webserv.hpp"

char**	get_env(request& request, std::string const& content_length, std::string document_root)
{
	std::map<std::string, std::string> env;
	env["CONTENT_LENGTH"] = content_length;
	if (request.headers_map["content-type"] == "test/file")
		env["CONTENT_TYPE"] = "text/html";
	else
		env["CONTENT_TYPE"] = request.headers_map["content-type"];
	env["DOCUMENT_ROOT"] = document_root;
	env["GATEWAY_INTERFACE"] = "CGI/1.1";
	size_t start;
	if (request.location.cgi_ext == ".bla")
		env["PATH_INFO"] = request.headers_map["full-target"];
	else if ((start = request.headers_map["target"].find(request.location.cgi_ext)) != std::string::npos)
	{
		start += request.location.cgi_ext.length();
		env["PATH_INFO"] = request.headers_map["target"].substr(start);
	}
	if (!env["PATH_INFO"].empty())
		env["PATH_TRANSLATED"] = env["DOCUMENT_ROOT"] + env["PATH_INFO"];
	env["QUERY_STRING"] = "";
	if ((start = request.headers_map["raw-target"].find("?")) != std::string::npos)
		env["QUERY_STRING"] = request.headers_map["raw-target"].substr(start + 1);
	env["REDIRECT_STATUS"] = "1"; // for php-cgi
	env["REMOTE_ADDR"] = request.client_ip;
	env["REQUEST_METHOD"] = request.headers_map["method"];
	env["REQUEST_URI"] = request.headers_map["full-target"];
	env["SCRIPT_FILENAME"] = env["DOCUMENT_ROOT"] + request.headers_map["target"];
	env["SCRIPT_NAME"] = request.headers_map["target"].substr(request.headers_map["target"].rfind("/"));
	env["SERVER_NAME"] = request.headers_map["host"].substr(0, request.headers_map["host"].find(":"));
	env["SERVER_PORT"] = request.headers_map["host"].substr(request.headers_map["host"].find(":") + 1);
	env["SERVER_PROTOCOL"] = request.headers_map["protocol-version"];
	env["SERVER_SOFTWARE"] = "Webserv/1.0";

	env = add_request_headers(request, env);

	return to_envp(env);
}

std::map<std::string, std::string>	add_request_headers(request& request, std::map<std::string, std::string> env)
{
	std::map<std::string, std::string>::iterator it = request.headers_map.begin();

	for (; it != request.headers_map.end(); it++)
		if (it->first[0] == 'x')
			env[format_http_header(it->first)] = it->second;

	return env;
}

std::string	format_http_header(std::string const& name)
{
	std::string tmp = name;

	for (size_t i = 0; i < tmp.size(); i++)
	{
		if (tmp[i] == '-')
			tmp[i] = '_';
		else
			tmp[i] = std::toupper(tmp[i]);
	}

	return "HTTP_" + tmp;
}

char**	to_envp(std::map<std::string, std::string> env)
{
	char** envp = new char*[env.size() + 1];

	size_t i = 0;
	std::map<std::string, std::string>::iterator it = env.begin();

	// std::cout << CYAN << "ENV\n"; // TESTING
	for (; it != env.end(); it++)
	{
		std::string	elem = it->first + "=" + it->second;
		// std::cout << elem << '\n'; // TESTING
		envp[i] = new char[elem.length() + 1];
		envp[i] = strcpy(envp[i], elem.c_str());
		i++;
	}
	// std::cout << RESET << '\n'; // TESTING

	envp[i] = NULL;

	return envp;
}
