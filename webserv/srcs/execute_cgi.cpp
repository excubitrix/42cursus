#include "webserv.hpp"

void	execute_cgi(webserv& webserv, request& request, location& location)
{
	init_fds(webserv);

	std::string input = get_input(request, location.root);
	// std::cout << "input: " << input << '\n'; // TESTING

	std::string document_root = get_document_root(webserv, location.root);
	// std::cout << "document_root: " << document_root << '\n'; // TESTING

	char** args = get_args(webserv.cwd, location.cgi_pass, document_root + request.headers_map["target"]);
	char** envp = get_env(request, SSTR(input.length()), document_root);

	if (write(webserv.fdin, input.c_str(), input.length()) != (ssize_t)input.length())
		throw (500);
	lseek(webserv.fdin, 0, SEEK_SET);

	std::string response;
	pid_t pid = fork();
	if (pid < 0)
	{
		close_fds(webserv);
		delete_arrays(args, envp);
		throw std::runtime_error("fork() failed");
	}
	else if (!pid)
	{
		/* change directory to document root */
		if (chdir((webserv.cwd + location.root).c_str()) < 0)
		{
			std::cerr << "Error: chdir() failed\n";
			exit(1);
		}

		dup2(webserv.fdin, STDIN_FILENO);
		dup2(webserv.fdout, STDOUT_FILENO);

		if (execve(*args, args, envp) < 0)
		{
			std::cerr << "Error: execve() failed\n";
			exit(1);
		}
	}
	else
	{
		char buffer[BUFFER_SIZE] = {0};

		int status;
		waitpid(-1, &status, 0);
		if ((status = WEXITSTATUS(status)) == 1)
			throw (500);
		lseek(webserv.fdout, 0, SEEK_SET);

		int	ret = 1;
		while (ret > 0)
		{
			memset(buffer, 0, BUFFER_SIZE);
			if ((ret = read(webserv.fdout, buffer, BUFFER_SIZE - 1)) < 0)
				throw (500);
			response += buffer;
		}
	}

	close_fds(webserv);
	delete_arrays(args, envp);

	edit_response_headers(request, response);
}

void	edit_response_headers(request& request, std::string response)
{
	// std::cout << RED "RESPONSE\n" RESET << response << '\n'; // TESTING

	size_t pos = response.find("\r\n\r\n");
	if (pos == std::string::npos)
	{
		request.response_header = SSTR(
			"HTTP/1.1 200 OK\n" <<
			"Content-length: " << response.length() << "\n" <<
			"Content-type: plain/text\r\n\r\n");
		request.response_body = response;
		return ;
	}

	std::string headers = response.substr(0, pos + 4);
	std::string body = response.substr(pos + 4);

	std::string status = "200 OK";
	if ((pos = headers.find("Status: ")) != std::string::npos)
	{
		pos += 8;
		size_t tmp = headers.find_first_of("\r\n", pos);
		status = headers.substr(pos, tmp - pos);
		headers.erase(0, headers.find_first_not_of("\r\n", tmp));
	}

	if (headers.find("HTTP/1.1") == std::string::npos)
		request.response_header = "HTTP/1.1 " + status + "\n";

	if (headers.find("Content-length") == std::string::npos)
		request.response_header += SSTR("Content-length: " << body.length() << "\n");

	request.response_header += headers;
	request.response_body = body;
	// std::cout << BOLD << GREEN << request.response_header << RESET << '\n'; // TESTING
	// std::cout << BOLD << GREEN << request.response_body.substr(0, 100) << "..." RESET << '\n'; // TESTING
}
