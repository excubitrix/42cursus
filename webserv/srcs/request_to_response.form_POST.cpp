#include "webserv.hpp"

std::string get_filename(request &request)
{
	/* find start position of filename */
	std::string filename_start_mark = "; filename=\"";
	std::vector<char>::iterator it_filename_start = std::search(
		request.body_data.begin(), request.body_data.end(),
		&filename_start_mark[0], &filename_start_mark[filename_start_mark.size()]);
	if (it_filename_start == request.body_data.end())
		throw (400);
	it_filename_start += filename_start_mark.length(); // filename starts after filename_start_mark
	
	/* find end position of filename */
	std::vector<char>::iterator it_filename_end = std::find(
		it_filename_start, request.body_data.end(), '\n');
	if (it_filename_end == request.body_data.end())
		throw (400);
	it_filename_end -= 2; // filename ends before '"\n'
	
	/* create filename std::string*/
	std::string filename(it_filename_start, it_filename_end);
	if (filename.empty() == true)
		throw (400);

	return (filename);
}



std::vector<char>::iterator find_data_start(request &request)
{
	std::string start_mark = "\n\r";
	std::vector<char>::iterator it_data_start = std::search(
		request.body_data.begin(), request.body_data.end(),
		&start_mark[0], &start_mark[start_mark.length()]);
	if (it_data_start == request.body_data.end())
		throw (400);
	it_data_start += 3; // skip over whitespace

	return (it_data_start);
}



std::vector<char>::iterator find_data_end(request &request,
	const std::vector<char>::iterator &it_data_start)
{
	/* find end position of data: */
	/* - extract boundary given in request header section: */
	/* - - find start position of boundary string */
	std::string content_type_header = request.headers_map["content-type"];
	size_t boundary_start_pos = content_type_header.find("=");
	if (boundary_start_pos == std::string::npos)
		throw (400);
	boundary_start_pos += 1; // boundary starts after '='

	/* - - extract boundary string */
	std::string boundary = "--" + content_type_header.substr(
		boundary_start_pos, std::string::npos);
	if (boundary == "--")
		throw (400);
	// std::cout << "boundary: " << boundary << std::endl; // TESTING

	/* - find end position of data */
	std::vector<char>::iterator it_data_end;
	it_data_end = std::search(
		it_data_start, request.body_data.end(),
		&boundary[0], &boundary[boundary.size()]);
	if (it_data_end == request.body_data.end())
		throw (400);
	it_data_end -= 2; // move to before whitespace after content
	
	return (it_data_end);
}



std::string create_file_on_server(
    request &request, const std::string &path)
{
	// std::cout << GREEN BOLD "UPLOADING" RESET << std::endl;

	std::string filename = get_filename(request);
	std::vector<char>::iterator it_data_start = find_data_start(request);
	std::vector<char>::iterator it_data_end = find_data_end(request, it_data_start);

	/* create file */
	// std::cout << BOLD RED << path + filename << RESET << std::endl; // TESTING
	std::ofstream output_file(path + filename, std::ofstream::binary);
    std::ostream_iterator<char> output_iterator(output_file);
    std::copy(it_data_start, it_data_end, output_iterator);
	output_file.close();
	if (!output_file)
		throw (500);

	return (path + filename);
}



void handle_webform_POST(const location &location, request &request)
{
	// std::cout << RED BOLD "location.upload_path: " << location.upload_path << RESET << std::endl; //TESTING

	/* if upload dir doesn't exists: try to create it */
	if (is_directory(location.upload_path) == false)
		if (mkdir_p(location.upload_path) == false)
			throw (500);

	/* attempt upload */
	std::string created_file = create_file_on_server(request, location.upload_path);

	std::string location_header = "Location: " + created_file + "\n"; // floor
	set_2xx_response_page(request, "201 Created", location_header);
}



/*
EXAMPLE WEB FORM UPLOAD REQUEST

--- request line ---
POST /upload.html HTTP/1.1
[...]
content-length: 325
content-type: multipart/form-data; boundary=----WebKitFormBoundarySqI5xrCS2WgamsIA
[...]

--- request.body ---
------WebKitFormBoundarySqI5xrCS2WgamsIA
Content-Disposition: form-data; name="fileToUpload"; filename="test.txt"
Content-Type: text/plain

Hello from uploadtestfile
Test ID: 1
------WebKitFormBoundarySqI5xrCS2WgamsIA
Content-Disposition: form-data; name="submit"

Upload
------WebKitFormBoundarySqI5xrCS2WgamsIA--

--------------------------------
*/
