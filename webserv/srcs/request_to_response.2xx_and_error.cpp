#include "webserv.hpp"

std::string create_accepted_methods_string(
	const std::vector<std::string> &accepted_methods)
{
	std::string allowed;

	allowed = "Allow: ";
	std::vector<std::string>::const_iterator it;
	for (it = accepted_methods.begin(); it != accepted_methods.end(); it++)
	{
		if (it != accepted_methods.begin())
			allowed += ", ";
		allowed += *it;
	}
	allowed += "\n";

	return (allowed);
}



void set_error_response(request &request, const int &error_code, location &location)
{
	std::string status = location.server->status_codes.at(error_code);
	request.response_body = get_response_body(location.error_pages[error_code]);

	std::string allowed;
	if (status == "405 Method Not Allowed")
		allowed = create_accepted_methods_string(location.accepted_methods);

	request.response_header = SSTR(
		"HTTP/1.1 " << status << "\n" <<
		"Content-Type: text/html\n" <<
		"Content-Length: " << request.response_body.length() << "\n" <<
		allowed <<
		"\n"
	);
}



void set_2xx_response_page(
	request &request, const std::string &status, const std::string &location_header)
{
	if (status == "200 OK")
		request.response_body = get_response_body("www/200.html");
	else
		request.response_body = get_response_body("www/201_created.html");

	request.response_header = SSTR(
		"HTTP/1.1 " << status << "\n"
		<< "Content-Type: text/html\n"
		<< "Content-Length: " << request.response_body.length() << "\n"
		<< location_header
		<< "\n");
}
