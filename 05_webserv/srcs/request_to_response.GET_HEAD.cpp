#include "webserv.hpp"

bool URI_is_accessible(const std::string &path)
{
	std::ifstream file(path);

	/* If ifstream wasn't successfully created, the file isn't accessable */
	if (!file)
		return (false);
	else
	{
		file.close();
		return (true);
	}
}



bool check_URI_existence(request &request)
{
	std::string target(request.headers_map["target"]);
	// std::cout << "path: " << request.location.root + target << "\n"; // TESTING

	if (is_file(request.location.root + target))
		// std::cout << "FILE" << '\n'; // TESTING
		;
	else if (is_directory(request.location.root + target)
		&& request.location.autoindex == true)
			return (true);
	else
		throw (404);

	return (false);
}



void handle_location_aliasing(request &request)
{
	std::string target(request.headers_map["target"]);

	if (!is_directory(request.server.root + request.location.name)
		&& !is_file(request.server.root + request.location.name))
	{
		if (request.location.name[request.location.name.length() - 1] == '/')
			target = target.replace(0, request.location.name.length() - 1, "");
		else
			target = target.replace(0, request.location.name.length(), "");
	}
	
	if (target.empty())
		target += "/";

	request.headers_map["target"] = target;
}



void set_response(request &request)
{
	std::string target = request.headers_map["target"];
	request.response_body = get_response_body(request.location.root + target);
	std::string content_type = get_content_type("200 OK", target);
	request.response_header = SSTR(
		"HTTP/1.1 200 OK\n"
		<< "Content-Type: " << content_type << "\n"
		<< "Content-Length: " << request.response_body.length() << "\n"
		<< "\n");
}



/*
- check if cgi
- check if the target (requested URI) is an alias (a location that refers to
  another location on the server) and if so change the target to the URI it
  refers to
- check if the target exists or if the target should trigger the return of an
  autoindex page
- check if the target is accessible
- create and return a response that holds the resource the URI indicated
*/

void handle_GET_or_HEAD_request(const location &location, request &request)
{

	bool autoindex = check_URI_existence(request);

	if (autoindex == true)
		return (create_autoindex_response(request, location));
	// std::cout << "target: '" << target << "'\n"; // TESTING

	if (URI_is_accessible(location.root + request.headers_map["target"]) == false)
		throw (403);

	set_response(request);
}
