#include "internalCounter.h" 
#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std;

int internalCounter() {
    int connection = 0; 

    while (true) {
        cout << "Started the counter..." << endl;
        auto future = std::async(counter, 1, "10 Minutes");
        connection = future.get();

        //cout << connection << endl; 
    }

    return connection; 
} 