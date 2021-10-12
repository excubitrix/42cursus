#include "webserv.hpp" 

void set_response(webserv &webserv, request &request)
{
	/* If a POST request is sent (via the upload.html page) or a DELETE request
	is sent (via the delete.html page), then the content of the request is
	processed separately. But apart from that the request is handled in the same
	manner as a regular GET request. */
	if (request.headers_map["method"] == "POST"
	&& request.headers_map["full-target"] == "/upload.html")
		return (handle_webform_POST(request.location, request));
	/* If a GET request is sent via the get_form page with a query string, the
	query string is parsed and a page is returned that lists the parsed data. */
	else if (request.headers_map["method"] == "GET"
	&& request.headers_map["full-target"].find("/get_form.html?") != std::string::npos)
		return (create_get_form_response(request));
	else if (request.headers_map["method"] == "DELETE")
		return (handle_DELETE_request(request.location, request));
	else if (request.headers_map["method"] == "PUT")
		return (handle_PUT_request(request.location, request));
	else if (request.location.cgi)
		return (execute_cgi(webserv, request, request.location));
	else if (request.headers_map["method"] == "POST")
		return (handle_POST_request(request.location, request));
	else
		return (handle_GET_or_HEAD_request(request.location, request));
}



bool request_method_allowed(request &request, const location &location)
{
	if (std::find(
		location.accepted_methods.begin(),
		location.accepted_methods.end(),
		request.headers_map["method"]) != location.accepted_methods.end())
		return (true);
	else
		return (false);
}



void set_redirection_response(request &request, context *cxt)
{
	request.response_header = SSTR(
		"HTTP/1.1 " << request.server.status_codes[cxt->return_code] << "\n" <<
		"Location: " << cxt->redirect << "\r\n\r\n");
}



/*
- check if URI should trigger redirection
- check if method is allowed
- set an appropriate response
*/
void request_to_response(webserv& webserv, request &request)
{
	handle_location_aliasing(request);
	if (is_directory(request.location.root + request.headers_map["target"])
		&& request.location.autoindex == false)
		select_index(request);
	check_for_cgi(request);
	// std::cout << "location: '" << request.location.name << "'\n"; // TESTING

	if (request_method_allowed(request, request.location) == false)
		throw (405);
	if (!request.server.redirect.empty()) // server redirection w/ location
		return (set_redirection_response(request, &request.server));
	if (request.server.return_code != -1) // server redirection w/o location
		throw (request.server.return_code);
	if (!request.location.redirect.empty()) // location redirection w/ location
		return (set_redirection_response(request, &request.location));
	if (request.location.return_code != -1) // location redirection w/o location
		throw (request.location.return_code);
	set_response(webserv, request);
}
