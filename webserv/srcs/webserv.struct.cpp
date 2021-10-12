#include "webserv.hpp"

webserv::webserv(void)
{
	ignore_warnings = false;
	response_counter = 0;
	max_sd_in_set = -1;
	
	/* initialize ("zero out") the fd_sets */
	FD_ZERO(&master_set);
	FD_ZERO(&read_set);
	FD_ZERO(&write_set);
	
	timeout.tv_sec = 30;
	timeout.tv_usec = 0;
}

void webserv::set_path_to_config(char **argv)
{
	char tmp[BUFFER_SIZE];
	this->cwd = getcwd(tmp, BUFFER_SIZE);
	if (!this->cwd.c_str())
		throw std::runtime_error(strerror(errno));
	std::string name(argv[0]);
	this->cwd += "/" + std::string(argv[0]).substr(0, name.rfind("/") + 1);
	this->path_to_config = this->cwd + CONFIG_DIR;
}

void webserv::init_config_server_blocks(int argc, char **argv)
{
	for (int i = 0; i < argc; i++)
		if (!std::strcmp(argv[i], "-i"))
			ignore_warnings = true;
	if (argc == 1 || (argc == 2 && !std::strcmp(argv[1], "-i")))
		parse_config(*this, this->path_to_config + "default.conf");
	else if (argc == 2)
		parse_config(*this, this->path_to_config + std::string(argv[1]));
	else if (argc == 3 && std::strcmp(argv[2], "-i"))
		parse_config(*this, this->path_to_config + std::string(argv[2]));
	else
		throw std::runtime_error("bad arguments");
	std::cout << "--- SERVER CONFIGURATION ---" << std::endl; // TESTING
	// TESTING_print_servers(this->servers);
}
