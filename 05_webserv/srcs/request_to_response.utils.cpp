#include "webserv.hpp"

std::string get_content_type(const std::string &status, const std::string &URI)
{
	/* Only have to figure out content type if the status code is 200, because all error pages are text/html. */
	if (status == "200 OK")
	{
		/* extract what comes after the period, which would be the file extension */ 
		size_t last_period_pos = URI.find_last_of(".");
		std::string file_extension = URI.substr(last_period_pos + 1, URI.length());
		
		if (file_extension == "css")
			return ("text/css");
		else if (file_extension == "ico")
			return ("image/ico");
		else if (file_extension == "txt")
			return ("text/plain");
		else if (file_extension == "jpg")
			return ("image/jpg");
		else if (file_extension == "jpeg")
			return ("image/jpeg");
		else if (file_extension == "png")
			return ("image/png");
	}
	return ("text/html");
}



std::string get_response_body(const std::string &html_page_URI)
{
	/* create ifstream with requested resource */
	std::ifstream file;
	file.open(html_page_URI);

	/* put the requested resource in a std::string variable */
	std::string response_body((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	
	file.close();

	return (response_body);
}
