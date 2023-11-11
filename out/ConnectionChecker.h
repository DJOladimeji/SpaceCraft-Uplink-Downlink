#pragma once 

#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <time.h>

using namespace std;
using namespace chrono; 

int checkConnection(bool& is_4_minute_timer, auto& start_time, string from);

