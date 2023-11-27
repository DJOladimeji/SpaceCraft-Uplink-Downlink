#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include "crow_all.h"
#include <regex>

using namespace crow;
using namespace std;

int createSocketAndConnect_SpaceCraft(string host, int port);
char* SendToSpaceCraft(crow::json::rvalue json_data, int port);