//store the data when the timer has run out  

#include "Buffer.h"

void Buffer::add_to_Buffer(crow::json::rvalue message_to_be_buffered) {
	messages.push_back(message_to_be_buffered);
}

vector<crow::json::rvalue> Buffer::remove_from_buffer() {
	return messages;
}

int Buffer::Buffer_size() {
	return messages.size(); 
}