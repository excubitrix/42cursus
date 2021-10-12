#ifndef REQUEST_STRUCT_HPP
#define REQUEST_STRUCT_HPP

#define URI_MAX_LENGTH 300

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

#include "context.struct.hpp" // server struct, location struct
#include "webserv.hpp"

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>

struct webserv;

struct request
{
	/* request.struct.cpp */
	request(void);
	request(std::string client_ip);
	void process_data(const char *data, const size_t &data_size, int sd, webserv &webserv);
	void parse_URI_query(void);

	/* request.struct.parse_first_line.cpp */
	void parse_first_line(void);
	void set_method(const std::string &request, size_t &current_pos);
	void set_target(const std::string &request, size_t &current_pos);
	void set_protocol_version(const std::string &request, size_t &current_pos);
	
	/* request.struct.parse_headers.cpp */
	void parse_headers(void);
	
	/* request.struct.content_data.cpp */
	void collect_body(const char *data, const size_t &data_size);
	void copy_from_headers_data(void);
	void append_requests_data(const char *data, const size_t &data_size);

	/* request.struct.chunked.cpp */
	bool collect_body_chunked(const char *data, const size_t &data_size);
	void parse_chunked_data(void);
	unsigned int convert_hex_str_to_int(std::string chunk_size_hex);

	bool								data_contains_headers;
	std::vector<char>					headers_data;
	std::map<std::string, std::string>	headers_map;
	std::vector<char>					body_data;
	std::map<std::string, std::string>	URI_query_map;
	
	/* in_use:
	- true: this request instantiation is currently being used
	- initialised to false in integrate_new_connection()
	- set to true when the request struct is initialised in
	  handle_selected_sds()
	- set back to false in connect_to_existing_sd(), after sending the response */
	bool			in_use;

	unsigned int	content_length;
	unsigned int	content_nbytes_received;

	bool			first_line_received;
	bool			headers_received;
	bool			request_received;

	std::string		response_header;
	std::string		response_body;
	std::string		response;
	bool			response_ready_to_send;
	int				total_bytes_sent;
	int				bytes_left_to_send;

	std::string		client_ip;
	
	server			server;
	location		location;
};

server&		select_server(webserv& webserv, std::string ip, std::string host, int sd);
location&	select_location(server server, std::string URI);

#endif
