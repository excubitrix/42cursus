#include "request.struct.hpp"

/* request-line = method SP request-target SP HTTP-version CRLF */
void request::parse_first_line(void)
{
	/* convert char array to string to use string's methods */
	std::vector<char>::iterator it_first_line_end = std::find(
		headers_data.begin(), headers_data.end(), '\n');
	std::string request(headers_data.begin(), it_first_line_end);
	
	size_t current_pos = 0;

	set_method(request, current_pos);
	set_target(request, current_pos);
	set_protocol_version(request, current_pos);

	first_line_received = true;
	// std::cout << CYAN " - processing: request line √" RESET << std::endl; // TESTING
	
	/* erase what has been parsed; what remains belongs to the body */
	headers_data.erase(headers_data.begin(), it_first_line_end + 1);
}



void request::set_method(const std::string &request, size_t &current_pos)
{
	size_t word_end_pos = request.find(" ");
	if (word_end_pos == std::string::npos)
		throw std::string("400 Bad request");
	headers_map["method"] = request.substr(current_pos, word_end_pos - current_pos);
	
	if (headers_map["method"].empty())
		throw std::string("400 Bad request");

	/* check if method is implemented */
	if (headers_map["method"] != "GET"
		&& headers_map["method"] != "POST"
		&& headers_map["method"] != "DELETE"
		&& headers_map["method"] != "HEAD"
		&& headers_map["method"] != "PUT"
		)
	{
		std::cout << "method: " << headers_map["method"] << '\n';
		throw std::string("501 Not Implemented");
	}

	current_pos = word_end_pos + 1;
}



std::string decode_URL(const std::string &URL)
{
    std::string decoded;
    for (size_t i = 0; i < URL.length(); i++)
	{
        if(URL[i] == '%')
		{
			unsigned int c;
			std::istringstream(URL.substr(i + 1, 2).c_str()) >> std::hex >> c;
            decoded += c;
            i += 2;
        }
		else if (URL[i] == '+')
			decoded += ' ';
		else
			decoded += URL[i];
    }
    return decoded;
}

void request::set_target(const std::string &request, size_t &current_pos)
{
	size_t word_end_pos = request.find(" ", current_pos);
	if (word_end_pos == std::string::npos)
		throw std::string("400 Bad request");
	headers_map["raw-target"] = request.substr(current_pos, word_end_pos - current_pos);

	if (headers_map["raw-target"].empty())
		throw std::string("400 Bad request");
		
	if (headers_map["raw-target"].length() > URI_MAX_LENGTH) // URI_MAX_LENGTH set in request.struct.hpp
		throw std::string("414 URI Too Long");
	
	/* decode URL */
	headers_map["full-target"] = decode_URL(headers_map["raw-target"]);

	size_t pos;
	if ((pos = headers_map["full-target"].find("?")) != std::string::npos)
		headers_map["target"] = headers_map["full-target"].substr(0, pos);
	else
		headers_map["target"] = headers_map["full-target"];

	current_pos = word_end_pos + 1;
}



void request::set_protocol_version(const std::string &request, size_t &current_pos)
{
	if (request.find_first_of("\r\n", current_pos) != std::string::npos) // floor
	{
		headers_map["protocol-version"] = request.substr(
			current_pos, request.find_first_of("\r\n", current_pos) - current_pos);
	}
	else
		headers_map["protocol-version"] = request.substr(current_pos);

	if (headers_map["protocol-version"].empty())
		throw std::string("400 Bad request");

	if (headers_map["protocol-version"].find("HTTP/1.") == std::string::npos)
		throw std::string("505 HTTP Version Not Supported");
}
