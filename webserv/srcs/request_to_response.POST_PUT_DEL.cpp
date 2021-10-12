#include "webserv.hpp"

void create_file_on_server(
	const request &request, std::string path, const std::string &filename)
{
	// std::cout << "creating file on server..." << std::endl; // TESTING

	/* append '/' to path if it's not present */
	if (path[path.length() - 1] != '/')
		path += "/";
	
	/* write data to file */
	std::ofstream output_file(path + filename, std::ofstream::binary);
    std::ostream_iterator<char> output_iterator(output_file);
    std::copy(request.body_data.begin(), request.body_data.end(), output_iterator);
	output_file.close();
	if (!output_file)
		throw (500);
}



std::string find_untaken_name(const std::string &upload_path)
{
	std::string filename;
	int i = 1;
	while (true)
	{
		filename = "upload" + SSTR(i);
		if (is_file(upload_path + filename) == false)
			break ;
		i++;
	}

	return (filename);
}



void handle_POST_request(const location &location, request &request)
{
	if (request.body_data.empty() == true)
		return (set_2xx_response_page(request, "200 OK", ""));

	/* if upload dir doesn't exists: create it */
	if (is_directory(location.upload_path) == false)
		if (mkdir_p(location.upload_path) == false)
			throw (500);

	std::string filename = find_untaken_name(location.upload_path);

	create_file_on_server(request, location.upload_path, filename);

	std::string location_header = "Location: " + location.upload_path + filename + "\n";
	set_2xx_response_page(request, "201 Created", location_header);
}



void handle_PUT_request(const location &location, request &request)
{
	if (request.body_data.empty() == true)
		return (set_2xx_response_page(request, "200 OK", ""));

	std::string filename = request.headers_map["full-target"];
	std::string path = location.root;

	/* if URI ends with a slash and so doesn't specify a file: return 400 error */
	if (request.headers_map["full-target"][request.headers_map["full-target"].length() - 1] == '/')
		throw (400);

	/* if URI is a path with dirs, parse it and create dirs if needed */
	size_t filename_start_pos = request.headers_map["full-target"].find_last_of("/");
	if (filename_start_pos != std::string::npos)
	{
		filename = request.headers_map["full-target"].substr(filename_start_pos + 1);
		path += request.headers_map["full-target"].substr(0, filename_start_pos);
		
		if (is_directory(path) == false)
			if (mkdir_p(path) == false)
				throw (500);
	}

	create_file_on_server(request, path, filename);
	
	std::string location_header = "Location: " + path + filename + "\n";
	set_2xx_response_page(request, "201 Created", location_header);
}



void handle_DELETE_request(const location &location, request &request)
{
	std::string target(location.root + request.headers_map["full-target"]);

	std::cout << BOLD RED "DELETE request for: " << target << RESET << std::endl; // TESTING

	if (is_file(target) == false)
        throw (400);
	
	/* execute delete (and `echo $?` for exit status code) */
	char buf[128];
	std::string exit_status;
	const std::string commands = "rm " + target + " ; echo $?";
	FILE* pipe = popen(commands.c_str(), "r");
	if (pipe == NULL)
        throw (500);
	
	while (fgets(buf, sizeof buf, pipe) != NULL)
		exit_status += buf;
	
	if (pclose(pipe) == -1)
        throw (500);
	
	/* exit_status == "0\n" means delete was successful */
	if (exit_status == "0\n")
		return (set_2xx_response_page(request, "200 OK", ""));
	throw (400);
}
