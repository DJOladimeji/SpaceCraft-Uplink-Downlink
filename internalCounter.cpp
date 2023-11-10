#include "internalCounter.h" 
#include <iostream>
#include <thread>
#include <chrono>
#include <future> 

using namespace std;

int internalCounter(auto *start_time) {
    int minutes = counter(&start_time);
    int connection = 0;

    if (minutes > 14) {
        start_time = startCounter(); 
        connection = 1;
    }
    else if (minutes < 4) {
        connection = 1;
    }
    else {
        connection = 0;
    }

    return connection;
}