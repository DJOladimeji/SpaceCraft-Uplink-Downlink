#include <iostream>
#include <string>
#include "crow_all.h"
#include "CheckBufferStatus.h"

using namespace std;

Result checkJsonArrayStatus(Buffer buffer)  
{
    Result result; 

    if (buffer.Buffer_size() == 0)
    {
        result.status = "JSON array is empty."; 
    }
    else
    {
        result.status = "JSON array is non-empty and valid."; 
    }

    return result;
}


