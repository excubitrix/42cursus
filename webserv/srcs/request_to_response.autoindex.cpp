#include "webserv.hpp"

std::vector<std::string> get_dir_content(const std::string &path)
{
	std::vector<std::string> content_list;
	struct dirent *entry;
	DIR *dir = opendir(path.c_str());

	if (dir == NULL)
	{
		perror("Error: opendir()");
		throw (500);
	}
	
	while ((entry = readdir(dir)) != NULL)
		content_list.push_back(entry->d_name);
	
	if (closedir(dir) == -1)
	{
		perror("Error: closedir()");
		throw (500);
	}

	return (content_list);
}



void append_slash_to_dirs(
	std::vector<std::string> &content_list, const std::string path)
{
	std::vector<std::string>::iterator it;
	for (it = content_list.begin(); it != content_list.end(); it++)
		if (is_directory(path + *it) == true)
			*it += "/";
}



std::string create_dir_content_html(
	const std::vector<std::string> &dir_content_vector, const std::string &folder)
{
	std::string dir_content_html;
	std::vector<std::string>::const_iterator it;
	for (it = dir_content_vector.begin(); it != dir_content_vector.end(); it++)
	{
		dir_content_html += "<li><a href=\"";
		dir_content_html += folder + *it;
		dir_content_html += "\">";
		dir_content_html += *it;
		dir_content_html += "</a></li>\n";
	}

	return (dir_content_html);
}



std::vector<char> create_html_template_vector(const std::string URI)
{
	/* index.html file - ifstream */
	std::ifstream file_stream(URI);
	if (!file_stream)
		throw (500);

	/* ifstream - vector<char> */
	std::vector<char> html_template;
	std::copy(std::istream_iterator<char>(file_stream >> std::noskipws),
		std::istream_iterator<char>(), std::back_inserter(html_template));
	if (html_template.empty() == true)
		throw (500);

	return (html_template);
}



void insert_string_into_template(
	std::vector<char> &html_template, const std::string &insert, const std::string location)
{
	/* find string - vector<char> */
	std::vector<char>::iterator insert_pos = std::search(
		html_template.begin(), html_template.end(),
		&location[0], &location[location.length()]);
	if (insert_pos == html_template.end())
		throw (500);
	
	/* remove string - vector<char> */
	html_template.erase(insert_pos, insert_pos + location.length());
	/* insert string - vector<char> */
	html_template.insert(insert_pos, insert.begin(), insert.end());
}



void assemble_and_set_response(
	request &request, const std::vector<char> &html_template, const std::string &folder)
{
	/* vector<char> - string */
	std::string response_body(html_template.begin(), html_template.end());
	if (response_body.empty())
		throw (500);
	request.response_body = response_body;

	request.response_header = SSTR(
		"HTTP/1.1 200 OK" << "\n"
		<< "Content-Type: text/html\n"
		<< "Content-Length: " << request.response_body.length() << "\n"
		<< "AutoIndex: " << folder << "\n"
		<< "\n"
	);
}



/*
- create a list of files and directories that are contained in the directory for
  which we need an autoindex page
- '/' is appended to directories in the list to 1) indicate they are directories
  and 2) because when they are then used as the href attribute in an <a> tag,
  they will form functional links to their respective directories
- remove the first two dir_content_vector entries as those contain '.' and '..'
- load a premade html template and insert the content list into it (as well as
  an appropriate header)
- set a response with the customized template
*/
void create_autoindex_response(
    request &request, const location &location)
{
	std::string folder = request.headers_map["target"];
	std::vector<std::string> dir_content_vector = get_dir_content(
		location.root + folder);
	append_slash_to_dirs(dir_content_vector, location.root + folder);
	dir_content_vector.erase(dir_content_vector.begin(), dir_content_vector.begin() + 2);
	// TESTING_print_vector_string(dir_content_vector); // TESTING
	std::string dir_content_html = create_dir_content_html(dir_content_vector, folder);
	std::vector<char> html_template = create_html_template_vector(
        "www/templates/index_template.html");
	insert_string_into_template(
        html_template, folder, "<!-- insert header here -->");
	insert_string_into_template(html_template, dir_content_html
		, "<!-- insert directory listing here -->");
	assemble_and_set_response(request, html_template, folder);
}
