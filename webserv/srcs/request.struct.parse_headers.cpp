#include "request.struct.hpp"

void char_tolower(char &c)
{
	c = std::tolower(c);
}



std::string get_name(const std::string &request, size_t &current_pos)
{
	size_t name_end_pos = request.find(":", current_pos);
	std::string name = request.substr(current_pos, name_end_pos - current_pos);
	if (name.empty()
	|| name.find_first_of(" \t\r\n") != std::string::npos)
		throw std::string("400 Bad request");
	/* convert name to lowercase for uniformity, as names should be handled case-insensitively */
	std::for_each(name.begin(), name.end(), char_tolower);
	current_pos = name_end_pos + 1;

	return (name);
}



std::string trim_whitespace(const std::string &str, std::string whitespace = " \t")
{
	size_t str_start = str.find_first_not_of(whitespace);
	if (str_start == std::string::npos)
		return (""); // no content

	size_t str_end = str.find_last_not_of(whitespace);
	size_t str_len = str_end - str_start + 1;

	return (str.substr(str_start, str_len));
}



std::string get_value(const std::string &request, size_t &current_pos, bool &reached_end)
{
	size_t value_end_pos = request.find("\r\n", current_pos);
	std::string value = request.substr(current_pos, value_end_pos - current_pos);
	value = trim_whitespace(value);
	
	current_pos = value_end_pos + 2;

	if (value_end_pos == std::string::npos)
		reached_end = true;

	return (value);
}



/* format: header-field = field-name ":" OWS field-value OWS (CRLF) */
void request::parse_headers(void)
{
	/* copy header section to string for ease of processing */
	std::string query = "\r\n\r\n";
	std::vector<char>::iterator it_header_end = std::search(
		headers_data.begin(), headers_data.end(), query.begin(), query.end());
	std::string request(headers_data.begin(), it_header_end);

	size_t current_pos = 0;
	bool reached_end = false;
	while (reached_end == false)
	{
		std::string name = get_name(request, current_pos);
		std::string value = get_value(request, current_pos, reached_end);
		headers_map[name] = value;
	}
	headers_received = true;
	// std::cout << CYAN " - processing: headers √" RESET << std::endl; // TESTING
	
	/* erase what has been processed; what remains belongs to the body */
	headers_data.erase(headers_data.begin(), it_header_end + 4);
	// TESTING_print_vector_char(headers_data);

	/* if there is no body: request has been entirely received
	else: set content_length member attribute */
	if (headers_map["content-length"] != "")
		content_length = param_to_u_int(headers_map["content-length"]);
	else if (headers_map["transfer-encoding"] == "chunked")
		;
		// std::cout << CYAN "receiving chunked data..." RESET << std::endl;
	else
		request_received = true;
}
