#include "request.struct.hpp"

/*
- if there is still data in headers_data, this data is part of the body, so we
  copy that into body_data
- else if data doesn't contains headers, we can store it as body_data
- in both of the previous cases, we only copy as much data into body_data as the
  content_length header specified
- after storing data, we check if all the data has been received
*/
void request::collect_body(const char *data, const size_t &data_size)
{
	/* if there is still data is headers_data, this data is part of the body */
	if (headers_data.empty() == false)
		copy_from_headers_data();
	else if (data_contains_headers == false)
		append_requests_data(data, data_size);
	
	if (content_nbytes_received == content_length)
	{
		// std::cout << CYAN "body data fully received" RESET << std::endl; // TESTING
		request_received = true;
	}
}



void request::copy_from_headers_data(void)
{
	if (headers_data.size() > content_length)
		body_data.insert(body_data.end(), headers_data.begin(), headers_data.begin() + content_length);
	else
		body_data.insert(body_data.end(), headers_data.begin(), headers_data.end());
	headers_data.clear();
	content_nbytes_received += body_data.size();
}



void request::append_requests_data(const char *data, const size_t &data_size)
{
	if (content_nbytes_received + data_size > content_length)
	{
		body_data.insert(body_data.end(), data, data + (content_length - content_nbytes_received));
		content_nbytes_received += (content_length - content_nbytes_received);
	}
	else
	{
		body_data.insert(body_data.end(), data, data + data_size);
		content_nbytes_received += data_size;
	}
}
