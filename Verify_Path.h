#pragma once
// verify_path.h
#include "crow_all.h"
#include <iostream>
#include <string>

using namespace std;
using namespace crow;


//#include <crow/json.h>

// Defining a structure to store the packet data
struct PacketData {
    std::string uri;
    std::string method;
    std::string path;
    crow::json::rvalue json_data; // JSON data associated with the packet
};

class VerifyPath {
public:
    bool verify(const crow::json::rvalue& json_data, PacketData& packet);

   
};

