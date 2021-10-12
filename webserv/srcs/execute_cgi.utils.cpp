#include "webserv.hpp"

void	init_fds(webserv& webserv)
{
	webserv.stdin_save = dup(STDIN_FILENO);
	webserv.stdout_save = dup(STDOUT_FILENO);

	webserv.fin = tmpfile();
	webserv.fout = tmpfile();

	webserv.fdin = fileno(webserv.fin);
	webserv.fdout = fileno(webserv.fout);
}

std::string	get_input(request& request, std::string const& document_root)
{
	if (request.headers_map["method"] == "POST"
		|| request.headers_map["method"] == "PUT")
		return std::string(request.body_data.begin(), request.body_data.end());
	else
		return get_response_body(document_root + request.headers_map["target"]);
}

std::string	get_document_root(webserv const& webserv, std::string const& root)
{
	if (root[0] != '/')
		return webserv.cwd + root;
	else
		return root;
}

char**	get_args(std::string cwd, std::string cgi_pass, std::string target)
{
	std::string executable_path = cwd;

	if (cgi_pass[0] != '/')
		executable_path += cgi_pass;
	else
		executable_path = cgi_pass;

	char** args = new char*[3];

	args[0] = new char[executable_path.length() + 1];
	args[0] = strcpy(args[0], executable_path.c_str());
	args[1] = new char[target.length() + 1];
	args[1] = strcpy(args[1], target.c_str());
	args[2] = NULL;

	return args;
}

void	close_fds(webserv& webserv)
{
	close(webserv.fdout);
	close(webserv.fdin);

	fclose(webserv.fout);
	fclose(webserv.fin);

	dup2(webserv.stdout_save, STDOUT_FILENO);
	dup2(webserv.stdin_save, STDIN_FILENO);

	close(webserv.stdout_save);
	close(webserv.stdin_save);
}

void	delete_arrays(char** args, char** envp)
{
	delete[] args[0];
	delete[] args[1];
	delete[] args;

	for (size_t i = 0; envp[i]; i++)
		delete[] envp[i];
	delete[] envp;
}
