#pragma once
#include <iostream>
#include <sstream>
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

using namespace crow;
using namespace std;

int createSocketAndConnect(char* host, int port);
char* SendToSpaceCraft(crow::json::rvalue json_data);