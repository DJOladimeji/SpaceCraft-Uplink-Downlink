#pragma once 
#include <thread>
#include <chrono>
#include <future>

using namespace std; 

int counter(int limit, const string& name) {
    int connection = 0;

    for (int i = 1; i <= limit; ++i) {
        this_thread::sleep_for(chrono::minutes(1));
        cout << name << " timer is at: " << i << " minute(s)\n";

        if (i <= 4) {
            connection = 1;
            cout << "Connection is positive" << endl;
        }
        else {
            connection = 0;
            cout << "Connection is negative" << endl; 
        }

    }

    cout << name << " timer has finished." << endl;

    return connection;
}