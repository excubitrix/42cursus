#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "context.struct.hpp"
# include "request.struct.hpp"

# include <sys/socket.h>
# include <netinet/in.h> // struct in_addr
# include <arpa/inet.h> // inet_addr
# include <sys/stat.h> // stat
# include <sys/wait.h> // waitpid
# include <string.h> // memset
# include <unistd.h>
# include <dirent.h> // opendir, readdir
# include <stdio.h> // perror
# include <errno.h> // perror
# include <fcntl.h>

# include <iostream>
# include <fstream>
# include <string>
# include <sstream> // stringstream

# include <algorithm> // find, search
# include <vector>
# include <map>

# define BACKLOG 1000000
# define CONFIG_DIR "config/"
# define ERROR_DIR "www/errors/"
# define BUFFER_SIZE 1024

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

# define SSTR(x) static_cast<std::ostringstream&>((std::ostringstream() << std::dec << x)).str() // convert ... to string

struct request;

struct webserv
{
	webserv(void);
	
	bool							ignore_warnings;
	std::string						cwd;
	std::string						path_to_config;
	std::vector<server>				servers;
	std::map<size_t, size_t>		port_map;
	std::map<size_t, std::string>	client_ip_map;
	struct fd_set					master_set, read_set, write_set;
	int								max_sd_in_set;
	int								response_counter; // TESTING
	struct timeval					timeout;
	std::map<int, request>			request_map;

	int		stdin_save;
	int		stdout_save;
	FILE*	fin;
	FILE*	fout;
	long	fdin;
	long	fdout;
	
	void set_path_to_config(char **argv);
	void init_config_server_blocks(int argc, char **argv);
};

/* execute_cgi.cpp */
void			execute_cgi(webserv& webserv, request& request, location& location);
void			edit_response_headers(request& request, std::string response);

/* execute_cgi.utils.cpp */
void			init_fds(webserv& webserv);
std::string		get_input(request& request, std::string const& document_root);
std::string		get_document_root(webserv const& webserv, std::string const& root);
char**			get_args(std::string cwd, std::string cgi_pass, std::string target);
void			close_fds(webserv& webserv);
void			delete_arrays(char** args, char** envp);

/* get_env.cpp */
char**			get_env(request& request, std::string const& content_length, std::string document_root);
std::map<std::string, std::string>	add_request_headers(request& request, std::map<std::string, std::string> env);
std::string		format_http_header(std::string const& name);
char**			to_envp(std::map<std::string, std::string> env);

/* parse_config.cpp */
void			parse_config(webserv& webserv, std::string const& path);
void			parse_server(webserv& webserv, std::string const& str);
void			parse_locations(webserv const& webserv, server& server,
					std::vector<std::string> const& locations);
void			edit_server(webserv& webserv, server& server);
void			edit_location(server& server, location& location);

/* parse_config.utils.cpp */
size_t			skip_space(std::string const& str, size_t start);
size_t			find_brace(std::string const& str, size_t start);
std::vector<std::string>	get_params(std::string const& params);
void			add_default_location(server& server);
void			check_server_names(webserv& webserv, server& server, std::string host_port);
std::string		extract_server_block(std::string const& str, size_t& pos, size_t& tmp);
std::string		extract_location_block(std::string const& str, size_t& pos, size_t& tmp);

/* request_to_response.2xx_and_error.cpp */
std::string		create_accepted_methods_string(
					const std::vector<std::string> &accepted_methods);
void			set_error_response(request &request, const int &error_code,
					location &location);
void			set_2xx_response_page(request &request, const std::string &status,
					const std::string &location_header);

/* request_to_response.autoindex.cpp */
std::vector<std::string> get_dir_content(const std::string &path);
void			append_slash_to_dirs(std::vector<std::string> &content_list,
					const std::string path);
std::string		create_dir_content_html(const std::vector<std::string> &dir_content_vector,
					const std::string &folder);
std::vector<char> create_html_template_vector(const std::string URI);
void			insert_string_into_template(std::vector<char> &html_template,
					const std::string &insert, const std::string location);
void			assemble_and_set_response(request &request,
					const std::vector<char> &html_template, const std::string &folder);
void			create_autoindex_response(request &request, const location &location);

/* request_to_response.cpp */
void			set_response(webserv &webserv, request &request);
bool			request_method_allowed(request &request, const location &location);
void			set_redirection_response(request &request, context *cxt);
void			request_to_response(webserv& webserv, request &request);

/* request_to_response.form_GET.cpp */
std::string		create_form_data_html(const std::map<std::string, std::string> &URI_map);
void			assemble_and_set_response(request &request,
					const std::vector<char> &file_vector);
void			create_get_form_response(request &request);

/* request_to_response.form_POST.cpp */
std::string		get_filename(request &request);
std::vector<char>::iterator find_data_start(request &request);
std::vector<char>::iterator find_data_end(request &request,
					const std::vector<char>::iterator &it_data_start);
std::string		create_file_on_server(request &request, const std::string &path);
void			handle_webform_POST(const location &location, request &request);

/* request_to_response.GET_HEAD.cpp */
bool			URI_is_accessible(const std::string &path);
bool			check_URI_existence(request &request);
void			handle_location_aliasing(request &request);
void			set_response(request &request);
void			handle_GET_or_HEAD_request(const location &location, request &request);

/* request_to_response.POST_PUT_DEL.cpp */
void			create_file_on_server(const request &request, std::string path,
					const std::string &filename);
std::string		find_untaken_name(const std::string &upload_path);
void			handle_POST_request(const location &location, request &request);
void			handle_PUT_request(const location &location, request &request);
void			handle_DELETE_request(const location &location, request &request);

/* request_to_response.utils.cpp */
std::string		get_content_type(const std::string &status, const std::string &URI);
std::string		get_response_body(const std::string &html_page_URI);

/* select.cpp */
bool			select_index(request& request);
void			check_for_cgi(request& request);

/* server.cpp */
void 			run_servers(webserv &webserv);
void			close_sds(webserv &webserv);

/* server.create_listen_sds.cpp */
std::vector<int> create_listen_sds(webserv &webserv);
int 			initialise_listen_sd(const std::string &ip, const int &port);

/* server.handle_selected_sds.cpp */
bool			handle_selected_sds(webserv &webserv, std::vector<int> listen_sds);
bool 			accept_new_connection(webserv &webserv, int &listen_sd);
void			integrate_new_connection(webserv &webserv, const int &new_sd, const sockaddr_in &client_addr, const int &listen_sd);
bool			connect_to_existing_sd(webserv &webserv, const int &sd, request &request);
bool			receive_and_process_request_data(webserv &webserv, const int &sd, request &request);
bool			send_response(webserv &webserv, const int &sd, request &request);
void			close_sd(webserv &webserv, const int &sd);

/* set_directive.cpp */
void			set_directive(webserv const& webserv, context* context, std::string type,
					std::string const& str, size_t& pos, size_t& tmp);
void			set_listen(webserv const& webserv, context* cxt, std::vector<std::string> values);
void			set_server_names(webserv const& webserv, context* cxt, std::vector<std::string> values);
void			set_root(webserv const& webserv, context* cxt, std::vector<std::string> values);
void			set_index(webserv const& webserv, context* cxt, std::vector<std::string> values);
void			set_accepted_methods(webserv const& webserv, context* cxt, std::vector<std::string> values);
void			set_autoindex(webserv const& webserv, context* cxt, std::vector<std::string> values);
void			set_client_max_body_size(webserv const& webserv, context* cxt, std::vector<std::string> values);
void			set_error_page(webserv const& webserv, context* cxt, std::vector<std::string> values);
void			set_cgi(webserv const& webserv, context* cxt, std::vector<std::string> values);
void			set_upload_path(webserv const& webserv, context* cxt, std::vector<std::string> values);
void			set_return(webserv const& webserv, context* cxt, std::vector<std::string> values);

/* set_directive.utils.cpp */
size_t			param_to_u_int(std::string const& value);
std::string		conform_path(std::string const& param, bool trailing_slash);
void			check_port(server const& server, size_t const& new_port);
bool			is_ip(std::string str);

/* utils */
bool			is_file(std::string path);
bool			is_directory(std::string path);
std::string		ft_inet_ntoa(struct in_addr in);
bool			mkdir_p(std::string path);



/* tests */
void            TESTING_print_parsed_request(request request);
void            TESTING_print_ready_sockets(
				int max_sd_in_set, fd_set read_set, fd_set write_set);
void            TESTING_print_vector_char(std::vector<char> vector);
void			TESTING_print_vector_string(std::vector<std::string> content_list);
void	        TESTING_print_servers(std::vector<server> servers);
void			TESTING_print_response(std::string header, std::string body);

#endif
