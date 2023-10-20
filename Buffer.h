#pragma once
#include <iostream>
#include "crow_all.h" 
#include "vector"

using namespace crow;
using namespace std;

class Buffer {
	vector<crow::json::rvalue> messages;

public:
	void add_to_Buffer(crow::json::rvalue message_to_be_buffered); 
	vector<crow::json::rvalue> remove_from_buffer();
};

