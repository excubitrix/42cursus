#include "webserv.hpp"

bool	handle_selected_sds(webserv& webserv, std::vector<int> listen_sds)
{
	bool sd_status;
	for (int sd = 0; sd <= webserv.max_sd_in_set; sd++)
	{
        sd_status = true;
		/* Check read_set for socket connections that have data for us to read */
		if (FD_ISSET(sd, &webserv.read_set))
		{
			/* Check if current checked sd is a listening socket. */
			for (std::vector<int>::iterator it = listen_sds.begin(); it != listen_sds.end(); it++)
				if (sd == (*it))
					return (accept_new_connection(webserv, (*it)));

			/* It's not a listening socket, so an existing connection is sending
			data. If the sd is already currently in use, that means we have
			already received data pertaining to this particular request. If it's
			not in use, then the incoming data is for a new request. */
			if (webserv.request_map[sd].in_use == false)
				webserv.request_map[sd] = request(webserv.client_ip_map[sd]);
			sd_status = connect_to_existing_sd(webserv, sd, webserv.request_map[sd]);
		}

		/* Check write_set for sockets that are ready to receive data that we
		want to send data to. */
		if (FD_ISSET(sd, &webserv.write_set)
			&& webserv.request_map[sd].response_ready_to_send == true
			&& webserv.request_map[sd].bytes_left_to_send > 0)
		{
			if (send_response(webserv, sd, webserv.request_map[sd]) == false)
				sd_status = false;
		}

		if (sd_status == false)
			close_sd(webserv, sd);

		usleep(1000); // for siege
	}
	return (true);
}



bool	accept_new_connection(webserv &webserv, int &listen_sd)
{
	std::cout << std::endl << BOLD "Listening sd " << listen_sd << " is readable" << RESET << std::endl; // TESTING
	
	sockaddr_in client_addr;
	socklen_t size = sizeof(client_addr);
	while (true)
	{
		int new_sd = accept(listen_sd, (sockaddr*)&client_addr, &size);
		std::cout << std::endl << BOLD "Accepting new connection: sd " << new_sd << RESET << std::endl; // TESTING
		if (new_sd == -1)
		{
			/* if accept() fails with EWOULDBLOCK, then we have accepted all of them */
			if (errno != EWOULDBLOCK)
			{
				std::cerr << "Error: accept() failed\n";
				return (false);
			}
			break ;
		}
		integrate_new_connection(webserv, new_sd, client_addr, listen_sd);
	}
	return (true);
}

void	integrate_new_connection(webserv &webserv, const int &new_sd,
			const sockaddr_in &client_addr, const int &listen_sd)
{
	/* Add the new incoming connection to the list of sockets that we're watching, (master_set). */
	std::cout << "New incoming connection: sd " << new_sd << "\n"; // TESTING
	FD_SET(new_sd, &webserv.master_set);
	if (new_sd > webserv.max_sd_in_set)
		webserv.max_sd_in_set = new_sd;

	std::string client_ip = ft_inet_ntoa(client_addr.sin_addr);
	// std::cout << "\nclient IP: " << client_ip << '\n'; // TESTING
	webserv.port_map[new_sd] = webserv.port_map[listen_sd];
	webserv.client_ip_map[new_sd] = client_ip;

	webserv.request_map[new_sd].in_use = false;
}



/*
- receive (partial) request and process it
	- if this fails, set an error response
- when request has been entirely received, process request to formulate a response
	- if this fails, set an error response
- if response if ready to send, set variables to prepare for sending
- return bool indicating if this went well
*/
bool	connect_to_existing_sd(webserv &webserv, const int &sd, request &request)
{
	bool sd_status;
	try
	{
		sd_status = receive_and_process_request_data(webserv, sd, request);
		if (request.request_received == true)
		{
			try
			{
				request_to_response(webserv, request);
			}
			catch (int error_code)
			{
				set_error_response(request, error_code, request.location);
			}
			request.response_ready_to_send = true;
		}
	}
	catch (std::string status)
	{
		request.response_header = "HTTP/1.1 " + status + "\n\n";
		sd_status = false;
		request.response_ready_to_send = true;
	}
	
	if (request.response_ready_to_send == true)
	{
		if (request.headers_map["method"] == "HEAD")
		{
			request.bytes_left_to_send = request.response_header.size();
			request.response = request.response_header;
		}
		else
		{
			request.bytes_left_to_send = request.response_header.size() + request.response_body.size();
			request.response = request.response_header + request.response_body;
		}
	}
	return (sd_status);
}

bool	receive_and_process_request_data(webserv &webserv, const int &sd, request &request)
{
	char request_buffer[500000] = {0};
	int nbytes = recv(sd, request_buffer, sizeof(request_buffer), 0);
	if (nbytes == -1)
	{
        std::cerr << "recv() returned -1 (sd " << sd << ")"; // TESTING
		perror(""); // TESTING
		return (false);
	}
	else if (nbytes == 0)
	{
		std::cerr << "recv() returned 0: Client closed connection (sd " << sd << ")" << std::endl ;
		return (false);
	}

	// std::cout << nbytes << " bytes received / "
	// << request.headers_data.size() + request.body_data.size() + nbytes << " in total" << std::endl; // TESTING

	request.process_data(request_buffer, nbytes, sd, webserv);
	
	return (true);
}



bool	send_response(webserv &webserv, const int &sd, request &request)
{
	int nbytes_sent = send(sd, &request.response[request.total_bytes_sent], request.bytes_left_to_send, 0);
	// std::cout << "nbytes_sent: " << nbytes_sent << std::endl; // TESTING
	if (nbytes_sent == -1)
	{
        std::cerr << "send() returned -1 (sd " << sd << ")"; // TESTING
		perror(""); // TESTING
		return (false);
	}
	else if (nbytes_sent == 0)
	{
		std::cerr << "Error: send() returned 0 (sd " << sd << ")";
		return (false);
	}

	request.total_bytes_sent += nbytes_sent;
	request.bytes_left_to_send -= nbytes_sent;
	
	if (request.bytes_left_to_send == 0)
	{
		request.in_use = false;
		webserv.response_counter++; // TESTING
		std::cout << "response # " << webserv.response_counter << " of a total of "
		<< request.total_bytes_sent << " bytes sent to sd " << sd << std::endl; // TESTING
	}
	
	return (true);
}



void	close_sd(webserv &webserv, const int &sd)
{
	std::cout << CYAN "closing sd " << sd << RESET << std::endl; // TESTING
	webserv.request_map[sd].in_use = false;
    close(sd);
	FD_CLR(sd, &webserv.master_set);
	/* If sd is the current max, set a new max. */
	if (sd == webserv.max_sd_in_set)
		while (FD_ISSET(webserv.max_sd_in_set, &webserv.master_set) == false)
			webserv.max_sd_in_set--;
}
