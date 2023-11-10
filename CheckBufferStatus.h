#pragma once
#include <iostream>
#include <string>
#include "crow_all.h"
#include "Buffer.h"

using namespace std;

struct Result 
{
    string status;
}; 

Result checkJsonArrayStatus(Buffer buffer);  
