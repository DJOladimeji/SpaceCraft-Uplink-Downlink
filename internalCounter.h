#pragma once 
#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <time.h>

using namespace std;
using namespace chrono; 

auto startCounter() {
    auto start_time = chrono::high_resolution_clock::now();

    return start_time;
}

int counter(auto start_time) {
    auto current_time = chrono::high_resolution_clock::now();

    cout << "Program has been running for " << chrono::duration_cast<chrono::minutes>
        (current_time - start_time).count() << " minutes" << endl;

    int minutes = chrono::duration_cast<chrono::minutes>(current_time - start_time).count();

    return minutes;
}