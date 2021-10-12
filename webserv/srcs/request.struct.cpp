#include "request.struct.hpp"

request::request(void) {}

request::request(std::string client_ip) : client_ip(client_ip)
{
	// std::cout << CYAN "parameter constructor: request\nClient IP: " << client_ip << '\n' << RESET; // TESTING
	in_use = true;
	content_length = 0;
	content_nbytes_received = 0;
	first_line_received = false;
	headers_received = false;
	request_received = false;
	response_ready_to_send = false;
	total_bytes_sent = 0;
	response_header = "";
	response_body = "";
	response = "";
}



/* 
- collect data coming in from recv() until all the headers have been received
	- the end of the headers is delimited with CRLF*2 (\r\n\r\n)
- parse the request's first line and the headers
- select server and location from configurations
- if there's body data, collect it
	- if the body data is chunked, unchunk it
*/
void request::process_data(
	const char *data, const size_t &data_size, int sd, webserv &webserv)
{
	// std::cout << CYAN "--- RECEIVED DATA---\n'" << data<< "'\n------------------------" RESET << std::endl; // TESTING

	data_contains_headers = false;
	if (first_line_received == false)
	{
		headers_data.insert(headers_data.end(), data, data + data_size);
		data_contains_headers = true;

		std::string query = "\r\n\r\n";
		if (std::search(headers_data.begin(), headers_data.end(),
			query.begin(), query.end()) == headers_data.end())
		{
			// std::cout << CYAN "headers data not (yet) fully received: not ready for processing" RESET << std::endl; // TESTING
			return ;
		}
		// std::cout << CYAN "headers data fully received: start processing..." RESET << std::endl; // TESTING

		parse_first_line();
		parse_headers();

		server = select_server(webserv, client_ip, headers_map["host"], sd);
		location = select_location(server, headers_map["target"]);
		location.server = &server;
		// std::cout << "location: '" << location.name << "'" << std::endl; // TESTING

		// std::cout << "content length: " << content_length << '\n'; // TESTING
		if (content_length > location.client_max_body_size)
			throw std::string("413 Request Entity Too Large");
	}

	if (headers_map["transfer-encoding"] == "chunked")
	{
		if (collect_body_chunked(data, data_size) == false)
			throw std::string("413 Request Entity Too Large");
	}
	else
		collect_body(data, data_size);
}



void request::parse_URI_query(void)
{
	std::string URI = headers_map["full-target"];
	std::map<std::string, std::string> URI_map;
	
	/* find first ?, before that is the base URI, skip over it */
	size_t base_URI_end_pos = URI.find("?");
	URI_map["base"] = URI.substr(0, base_URI_end_pos);
	size_t start_pos = base_URI_end_pos + 1;
	bool loop = true;
	while (loop)
	{
		/* find next =, before that is a key */
		size_t key_end_pos = URI.find("=", start_pos);
		if (key_end_pos == std::string::npos)
			break ;
		std::string key = URI.substr(start_pos, key_end_pos - start_pos);
		
		/* find next &, before that is the value */
		start_pos = key_end_pos + 1;
		size_t value_end_pos = URI.find("&", start_pos);
		if (value_end_pos == std::string::npos)
			loop = false;
		std::string value = URI.substr(start_pos, value_end_pos - start_pos);
		// std::cout << "value: '" << value << "'" << std::endl; // TESTING
		
		start_pos = value_end_pos + 1;

		URI_map[key] = value;
	}
	URI_query_map = URI_map;
}
