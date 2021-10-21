#include "webserv.hpp"

/********************************************************************/
/* ------------------- STATIC GLOBAL VARIABLES -------------------- */

static std::string const	directive[11] = {
	"listen",
	"server_name",
	"root",
	"index",
	"accepted_methods",
	"autoindex",
	"client_max_body_size",
	"error_page",
	"cgi_pass",
	"upload_path",
	"return"
};

typedef	void(*functionPtr)(
	webserv const& webserv, context* cxt, std::vector<std::string> values);

static functionPtr const	f[11] = {
	&set_listen,
	&set_server_names,
	&set_root,
	&set_index,
	&set_accepted_methods,
	&set_autoindex,
	&set_client_max_body_size,
	&set_error_page,
	&set_cgi,
	&set_upload_path,
	&set_return
};

/********************************************************************/
/* ---------------------- DISPATCH FUNCTION ----------------------- */

void	set_directive(webserv const& webserv, context* context, std::string type,
			std::string const& str, size_t& pos, size_t& tmp)
{
	std::string key(str.substr(pos, tmp - pos));
	for (size_t i = 0; i < 12; i++)
	{
		if (key == directive[i])
		{
			pos = tmp;
			while (pos != std::string::npos && str[pos] != ';')
				pos = skip_space(str, ++pos);
			if (pos == std::string::npos)
				throw std::runtime_error(type + ": " + key + ": expected a ';'");
			(*f[i])(webserv, context, get_params(str.substr(tmp, pos - tmp)));
			break ;
		}
		else if (i == 11)
			throw std::runtime_error(type + ": no such directive '" + key + "'");
	}
}

/********************************************************************/
/* ----------------------- SETTER FUNCTIONS ----------------------- */

/********************************************************************/
/* Syntax:	listen [address:]port;									*/
/* Default:	listen 0.0.0.0:8000;									*/
/* Context:	server													*/
/********************************************************************/

void	set_listen(webserv const& webserv, context* cxt, std::vector<std::string> values)
{
	(void)webserv;
	if (!dynamic_cast<struct server*>(cxt))
		throw std::runtime_error("listen: wrong context");
	server* server = dynamic_cast<struct server*>(cxt);
	if (!values.size())
		throw std::runtime_error("listen: missing parameter");
	if (values.size() > 1)
		throw std::runtime_error("listen: invalid parameter '" + values[1] + "'");
	size_t new_port;
	size_t pos = values[0].find(":");
	if (pos == std::string::npos)
	{
		if (values[0].find_first_not_of("0123456789") != std::string::npos)
			throw std::runtime_error("listen: missing or invalid port");
		new_port = param_to_u_int(values[0]);
		check_port(*server, new_port);
		server->host.push_back("0.0.0.0");
		server->port.push_back(new_port);
	}
	else
	{
		std::string tmp(values[0].substr(pos + 1));
		if (tmp.find_first_not_of("0123456789") != std::string::npos)
			throw std::runtime_error("listen: invalid port '" + tmp + "'");
		new_port = param_to_u_int(tmp);
		check_port(*server, new_port);
		std::string hostname = values[0].substr(0, pos);
		if (hostname == "localhost")
			hostname = "127.0.0.1";
		if (is_ip(hostname))
			server->host.push_back(hostname);
		else
			throw std::runtime_error("listen: invalid hostname '" + hostname + "'");
		server->port.push_back(new_port);
	}
}

/********************************************************************/
/* Syntax:	server_name name ...;									*/
/* Default:	server_name "";											*/
/* Context:	server													*/
/********************************************************************/

void	set_server_names(webserv const& webserv, context* cxt,
			std::vector<std::string> values)
{
	(void)webserv;
	if (!dynamic_cast<struct server*>(cxt))
		throw std::runtime_error("server_names: wrong context");
	server* server = dynamic_cast<struct server*>(cxt);
	if (!server->names.empty())
		throw std::runtime_error("server_names: duplicate directive");
	if (!values.size())
		throw std::runtime_error("server_names: missing parameter");
	for (size_t i = 0; i < values.size(); i++)
	{
		for (size_t j = 0; j < server->names.size(); j++)
			if (values[i] == server->names[j])
				throw std::runtime_error("server_names: duplicate parameter '" +
					values[i] + "'");
		server->names.push_back(values[i]);
	}
}

/********************************************************************/
/* Syntax:	root path;												*/
/* Default:	root www;												*/
/* Context:	server, location										*/
/********************************************************************/

void	set_root(webserv const& webserv, context* cxt, std::vector<std::string> values)
{
	(void)webserv;
	if (!cxt->root.empty())
		throw std::runtime_error("root: duplicate directive");
	if (!values.size())
		throw std::runtime_error("root: missing parameter");
	if (values.size() > 1)
		throw std::runtime_error("root: invalid parameter '" + values[1] + "'");
	cxt->root = conform_path(values[0], false);
	if ((cxt->root[0] != '/' && !is_directory(webserv.cwd + std::string(cxt->root)))
		|| !is_directory(std::string(cxt->root)))
		throw std::runtime_error("root: no such directory '" + values[0] + "'");
}

/********************************************************************/
/* Syntax:	index file ...;											*/
/* Default:	index index.html;										*/
/* Context:	server, location										*/
/********************************************************************/

void	set_index(webserv const& webserv, context* cxt, std::vector<std::string> values)
{
	(void)webserv;
	if (!cxt->index.empty())
		throw std::runtime_error("index: duplicate directive");
	if (!values.size())
		throw std::runtime_error("index: missing parameter");
	for (size_t i = 0; i < values.size(); i++)
	{
		for (size_t j = 0; j < cxt->index.size(); j++)
			if (values[i] == cxt->index[j])
				throw std::runtime_error("index: duplicate parameter '" + values[i] + "'");
		cxt->index.push_back(values[i]);
	}
}

/********************************************************************/
/* Syntax:	accepted_methods method ...;							*/
/* Default:	accepted_methods method GET;							*/
/* Context:	server, location										*/
/********************************************************************/

void	set_accepted_methods(webserv const& webserv, context* cxt,
			std::vector<std::string> values)
{
	(void)webserv;
	if (!values.size())
		throw std::runtime_error("accepted_methods: missing parameter");
	if (!cxt->accepted_methods.empty())
		throw std::runtime_error("accepted_methods: duplicate directive");
	for (size_t i = 0; i < values.size(); i++)
	{
		if (values[i] != "GET" && values[i] != "POST"
			&& values[i] != "DELETE" && values[i] != "NONE"
			&& values[i] != "HEAD" && values[i] != "PUT" // extra
			&& values[i] == "CONNECT" && values[i] == "OPTIONS" // not implemented
			&& values[i] == "TRACE" && values[i] == "PATCH") // not implemented
			throw std::runtime_error("accepted_methods: invalid parameter '" +
				values[i] + "'");
		for (size_t j = 0; j < cxt->accepted_methods.size(); j++)
			if (values[i] == cxt->accepted_methods[j])
				throw std::runtime_error("accepted_methods: duplicate parameter '" +
					values[i] + "'");
		if (cxt->accepted_methods.size() && values[i] == "NONE")
			throw std::runtime_error(SSTR("accepted_methods: cannot assign 'NONE', '"
				<< cxt->accepted_methods[0] << "' already present"));
		if (cxt->accepted_methods.size() && cxt->accepted_methods[0] == "NONE")
			throw std::runtime_error(SSTR("accepted_methods: cannot assign '" << values[i]
				<< "', 'NONE' already present"));
		cxt->accepted_methods.push_back(values[i]);
	}
}

/********************************************************************/
/* Syntax:	autoindex on | off;										*/
/* Default:	autoindex off;											*/
/* Context:	server, location										*/
/********************************************************************/

void	set_autoindex(webserv const& webserv, context* cxt, std::vector<std::string> values)
{
	(void)webserv;
	if (cxt->autoindex_set)
		throw std::runtime_error("autoindex: duplicate directive");
	if (!values.size())
		throw std::runtime_error("autoindex: missing parameter");
	if (values.size() > 1)
		throw std::runtime_error("autoindex: invalid parameter '" + values[1] + "'");
	if (values[0].compare("on") && values[0].compare("off"))
		throw std::runtime_error("autoindex: invalid parameter '" + values[0] + "'");
	if (!values[0].compare("on"))
		cxt->autoindex = true;
	else
		cxt->autoindex = false;
	cxt->autoindex_set = true;
}

/********************************************************************/
/* Syntax:	client_max_body_size size;								*/
/* Default:	client_max_body_size 1m;								*/
/* Context:	server, location										*/
/********************************************************************/

void	set_client_max_body_size(webserv const& webserv, context* cxt,
			std::vector<std::string> values)
{
	(void)webserv;
	if (cxt->client_max_body_size != -1)
		throw std::runtime_error("client_max_body_size: duplicate directive");
	if (!values.size())
		throw std::runtime_error("client_max_body_size: missing parameter");
	if (values.size() > 1)
		throw std::runtime_error("client_max_body_size: invalid parameter '" +
			values[1] + "'");
	char last = values[0][values[0].length() - 1];
	std::string tmp("0123456789kmg");
	if (tmp.find(last) == std::string::npos)
		throw std::runtime_error("client_max_body_size: invalid parameter '" +
			values[0] + "'");
	long mul = (last == 'k') ? 1000 : (last == 'm') ? 1000000 : (last == 'g') ?
		1000000000 : 1;
	if (last == 'k' || last == 'm' || last == 'g')
		tmp = values[0].substr(0, values[0].length() - 1);
	else
		tmp = values[0];
	if (tmp.empty() || tmp.find_first_not_of("0123456789") != std::string::npos)
		throw std::runtime_error("client_max_body_size: invalid parameter '" +
			values[0] + "'");
	cxt->client_max_body_size = mul * param_to_u_int(tmp);
}

/********************************************************************/
/* Syntax:	error_page code ... uri;								*/
/* Default:	error_page code www/errors/<code>.html					*/
/* Context:	server, location										*/
/********************************************************************/

void	set_error_page(webserv const& webserv, context* cxt, std::vector<std::string> values)
{
	if (values.size() < 2)
		throw std::runtime_error("error_page: missing parameter");
	std::string path(values[values.size() - 1]);
	for (size_t i = 0; i < values.size() - 1; i++)
	{
		if (values[i].find_first_not_of("0123456789") != std::string::npos)
			throw std::runtime_error("error_page: invalid parameter '" + values[i] + "'");
		size_t code = param_to_u_int(values[i]);
		if (code < 100 || code > 599)
			throw std::runtime_error(SSTR("error_page: invalid parameter '" << code << "'"));
		std::map<size_t, std::string>::iterator it = cxt->error_pages.begin();
		for (; it != cxt->error_pages.end(); it++)
			if (code == it->first && !it->second.empty())
				throw std::runtime_error(SSTR("error_page: duplicate parameter '" <<
					code << "'"));
		cxt->error_pages[code] = conform_path(path, false);
		if ((cxt->error_pages[code][0] != '/' && !is_file(webserv.cwd +
			cxt->error_pages[code]))
			|| !is_file(cxt->error_pages[code]))
			throw std::runtime_error("error_page: no such file '" + path + "'");
	}
}

/********************************************************************/
/* Syntax:	cgi_pass path;											*/
/* Default:	-														*/
/* Context:	location												*/
/********************************************************************/

void	set_cgi(webserv const& webserv, context* cxt, std::vector<std::string> values)
{
	(void)webserv;
	if (!dynamic_cast<struct location*>(cxt))
		throw std::runtime_error("cgi_pass: wrong context");
	location* location = dynamic_cast<struct location*>(cxt);
	if (strncmp(location->name.c_str(), "*.", 2))
		throw std::runtime_error("cgi_pass: directive not allowed");
	if (location->cgi)
		throw std::runtime_error("cgi_pass: duplicate directive");
	if (!values.size())
		throw std::runtime_error("cgi_pass: missing parameter");
	if (values.size() > 1)
		throw std::runtime_error("cgi_pass: invalid parameter '" + values[1] + "'");
	location->cgi_ext = location->name.substr(1);
	location->cgi_pass = conform_path(values[0], false);
	if ((location->cgi_pass[0] != '/' && !is_file(webserv.cwd +
		std::string(location->cgi_pass)))
		|| !is_file(std::string(location->cgi_pass)))
		throw std::runtime_error("cgi_pass: no such file '" + values[0] + "'");
	location->cgi = true;
}

/********************************************************************/
/* Syntax:	upload_path path;										*/
/* Default:	upload_path <server_root>/tmp/uploads/;					*/
/* Context:	server, location										*/
/********************************************************************/

void	set_upload_path(webserv const& webserv, context* cxt,
			std::vector<std::string> values)
{
	(void)webserv;
	if (!values.size())
		throw std::runtime_error("upload_path: missing parameter");
	if (values.size() > 1)
		throw std::runtime_error("upload_path: invalid parameter '" + values[1] + "'");
	if (!cxt->upload_path.empty())
		throw std::runtime_error("upload_path: duplicate directive");
	cxt->upload_path = conform_path(values[0], true);
}

/********************************************************************/
/* Syntax:	return code [uri];										*/
/* 			return uri;												*/
/* Default:	-														*/
/* Context:	server, location										*/
/********************************************************************/

void	set_return(webserv const& webserv, context* cxt, std::vector<std::string> values)
{
	(void)webserv;
	std::map<int, std::string> status_codes;
	if (dynamic_cast<struct server*>(cxt))
		status_codes = dynamic_cast<struct server*>(cxt)->status_codes;
	else if (dynamic_cast<location*>(cxt))
		status_codes = dynamic_cast<struct location*>(cxt)->server->status_codes;
	else
		throw std::runtime_error("return: parsing error");
	if (cxt->return_code != -1)
		throw std::runtime_error("return: duplicate directive");
	if (!values.size())
		throw std::runtime_error("return: missing parameter");
	if (values.size() > 2)
		throw std::runtime_error("return: invalid parameter '" + values[2] + "'");
	if (values[0].find_first_not_of("0123456789") != std::string::npos)
	{
		if (values.size() != 2)
		{
			cxt->return_code = 307;
			cxt->redirect = values[0];
		}
		else
			throw std::runtime_error("return: invalid parameter '" + values[0] + "'");
	}
	else
	{
		int code = param_to_u_int(values[0]);
		if (status_codes[code].empty())
			throw std::runtime_error(SSTR("return: not supported '" << code << "'"));
		if (values.size() != 2 && code / 100 == 3)
			throw std::runtime_error("return: missing parameter");
		if (values.size() == 2 && code / 100 != 3)
			throw std::runtime_error(SSTR("return: not a redirection '" << code << "'"));
		cxt->return_code = code;
		if (values.size() == 2)
		{
			std::string uri(values[1]);
			if (uri.rfind(":") != std::string::npos && strncmp(uri.c_str(), "http://", 7))
				throw std::runtime_error("return: uri: invalid syntax\nusage: "
					"[http://<hostname>:<port>]<target>");
			cxt->redirect = uri;
		}
	}
}
