#ifndef CONTEXT_STRUCT_HPP
# define CONTEXT_STRUCT_HPP

# include <string>
# include <vector>
# include <map>

struct context
{
	context(void);
	virtual ~context(void);

	std::string root;
	std::vector<std::string> index;
	std::vector<std::string> accepted_methods;
	bool autoindex;
	bool autoindex_set;
	long client_max_body_size;
	std::map<size_t, std::string> error_pages;
	std::string upload_path;
	int return_code;
	std::string redirect;
};

typedef struct server server;
typedef struct location location;

struct server : public context
{
	server(void);
	server(server const& src);
	server& operator=(server const& src);
	virtual ~server(void);

	std::vector<std::string> host;
	std::vector<size_t> port;
	bool default_server;
	std::vector<std::string> names;
	std::vector<location> locations;
	std::map<int, std::string> status_codes;
};

struct location : public context
{
	location(void);
	location(server& s);
	location(location const& src);
	location& operator=(location const& src);
	virtual ~location(void);

	server const* server;
	std::string name;
	bool cgi;
	std::string cgi_ext;
	std::string cgi_pass;
};

#endif
