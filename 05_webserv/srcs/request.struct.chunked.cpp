#include "request.struct.hpp"

/*
- if there is still data in headers_data, this data is part of the body, so we
  copy that into body_data
- else if data doesn't contains headers, we can store it as body_data
- after storing data, we check if the last chunk has been fully received. The
  end of the last chunk is marked with "0\r\n\r\n"
*/
bool request::collect_body_chunked(const char *data, const size_t &data_size)
{
	if (headers_data.empty() == false)
	{
		body_data.insert(body_data.end(), headers_data.begin(), headers_data.end());
		headers_data.clear();
	}
	else if (data_contains_headers == false)
		body_data.insert(body_data.end(), data, data + data_size);

	if (body_data.size() >= 5)
	{
		std::string ending(body_data.end() - 5, body_data.end());
		if (ending == "0\r\n\r\n")
		{
			request_received = true;
			// std::cout << CYAN "chunked data fully received: start processing..." RESET << std::endl; // TESTING
			parse_chunked_data();
			// std::cout << CYAN "chunked data processed" RESET << std::endl; // TESTING
			if (body_data.size() > (unsigned long)location.client_max_body_size)
				return (false);
		}
	}
	return (true);
}



/* Add all the chunks w/o hex numbers and delimiting CRLFs to a new vector. When
we've reached the end (chunk_size == 0), replace body_data with new vector. */
void request::parse_chunked_data(void)
{
	std::vector<char> new_vector;
	std::vector<char>::iterator it_current_pos = body_data.begin();
	std::vector<char>::iterator it_hex_number_end;
	std::string CRLF = "\r\n";
	unsigned int chunk_size;

	while (true)
	{
		it_hex_number_end = std::search(
			it_current_pos, body_data.end(), CRLF.begin(), CRLF.end());
		
		chunk_size = convert_hex_str_to_int(std::string(it_current_pos, it_hex_number_end));
		if (chunk_size == 0)
			break ;
		
		it_current_pos = (it_hex_number_end + CRLF.size());
		new_vector.insert(new_vector.end(), it_current_pos, it_current_pos + chunk_size);
		it_current_pos += chunk_size + CRLF.size();
	}
	body_data = new_vector;
}



unsigned int request::convert_hex_str_to_int(std::string chunk_size_hex)
{
	unsigned int chunk_size;
	std::stringstream ss;
	ss << std::hex << chunk_size_hex;
	ss >> chunk_size;
	// std::cout << "chunk_size: " << chunk_size << std::endl; // TESTING
	
	return (chunk_size);
}
