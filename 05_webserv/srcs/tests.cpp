#include "webserv.hpp"

void TESTING_print_vector_char(std::vector<char> vector)
{
    for (std::vector<char>::iterator it = vector.begin(); it != vector.end(); it++)
		std::cout << *it;
	std::cout << std::endl;
}

void TESTING_print_vector_string(std::vector<std::string> content_list)
{
	std::vector<std::string>::iterator it;
	for (it = content_list.begin(); it != content_list.end(); it++)
		std::cout << *it << ", ";
	
	std::cout << std::endl;
}

void TESTING_print_ready_sockets(int max_sd_in_set
, fd_set read_set, fd_set write_set)
{
    for(int test = 0; test <= max_sd_in_set; test++)
    {
    	if (FD_ISSET(test, &read_set))
    		std::cout << "\nselect()ed: ready for reading: sd " << test << std::endl;
    	if (FD_ISSET(test, &write_set))
    		std::cout << "ready for writing: sd " << test << std::endl;
    }
}

void TESTING_print_parsed_request(request request)
{
	std::cout << YELLOW "--- request line ---" << std::endl;
	std::cout << request.headers_map["method"]
	<< " " << request.headers_map["full-target"]
	<< " " << request.headers_map["protocol-version"] << std::endl;

	std::cout << YELLOW "--- request.headers_map ---" << std::endl;
	std::map<std::string, std::string>::iterator it;
	for (it = request.headers_map.begin(); it != request.headers_map.end(); it++)
		std::cout << it->first << ": " << it->second << std::endl;

	std::cout << "--- request.body.size() ---" << std::endl;
	std::cout << request.body_data.size() << std::endl;
	// for (std::vector<char>::const_iterator it = request.body_data.begin(); it != request.body_data.end(); ++it)
		// std::cout << *it;
	// std::cout << std::endl;
	std::cout << "--------------------------------"  RESET << std::endl;
}

void TESTING_print_response(std::string header, std::string body)
{
	(void)body;
	(void)header;
	
	std::cout << MAGENTA "\n--- SENDING RESPONSE ---\n'"
	<< header
	<< body
	<<  "'\n------------------------" RESET << std::endl;
}


void	TESTING_print_servers(std::vector<server> servers)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		std::cout << YELLOW << "Server #" << 1 + i << RESET << '\n';
		for (size_t j = 0; j < servers[i].host.size(); ++j)
		{
			std::cout << "host|port: " << servers[i].host[j] << ":" << servers[i].port[j];
			if (servers[i].default_server)
				std::cout << " default_server";
			std::cout << '\n';
		}
		std::cout << "server_name: ";
		for (size_t j = 0; j < servers[i].names.size(); ++j)
			std::cout << servers[i].names[j] << " ";
		std::cout << '\n'
				  << "root: " << servers[i].root << '\n'
				  << "index: ";
		for (size_t j = 0; j < servers[i].index.size(); ++j)
			std::cout << servers[i].index[j] << " ";
		std::cout << '\n'
				  << "accepted_methods: ";
		for (size_t j = 0; j < servers[i].accepted_methods.size(); ++j)
			std::cout << servers[i].accepted_methods[j] << " ";
		std::cout << '\n';
		if (servers[i].autoindex)
			std::cout << "autoindex: " << servers[i].autoindex << '\n';
		std::cout << "client_max_body_size: " << servers[i].client_max_body_size << '\n';
		// std::map<size_t, std::string>::iterator it = servers[i].error_pages.begin();
		// for (; it != servers[i].error_pages.end(); it++)
		// 	std::cout << "error_page [" << it->first << "] " << it->second << '\n';
		std::cout << "upload_path: " << servers[i].upload_path << '\n';
		std::vector<location>::iterator it2 = servers[i].locations.begin();
		for (; it2 != servers[i].locations.end(); it2++)
		{
			std::cout << CYAN BOLD << "- Location " << it2->name << RESET << '\n'
					  << "  root: " << it2->root << '\n'
					  << "  index: ";
			for (size_t j = 0; j < it2->index.size(); ++j)
				std::cout << it2->index[j] << " ";
			std::cout << '\n'
					  << "  accepted_methods: ";
			for (size_t j = 0; j < it2->accepted_methods.size(); ++j)
				std::cout << it2->accepted_methods[j] << " ";
			std::cout << '\n';
			if (it2->autoindex)
				std::cout << "  autoindex: " << it2->autoindex << '\n';
			std::cout << "  client_max_body_size: " << it2->client_max_body_size << '\n';
			// std::map<size_t, std::string>::iterator it = it2->error_pages.begin();
			// for (; it != it2->error_pages.end(); it++)
			// 	std::cout << "  error_page [" << it->first << "] " << it->second << '\n';
			std::cout << "  upload_path: " << it2->upload_path << '\n';
			if (it2->cgi)
				std::cout << "  cgi_pass " << it2->cgi_pass << '\n';
			if (it2->return_code != -1)
				std::cout << "  return [" << it2->return_code << "] " << it2->redirect << '\n';
		}
		if (servers[i].return_code != -1)
			std::cout << "return [" << servers[i].return_code << "] " << servers[i].redirect << '\n';
	}
}
