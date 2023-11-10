#include <iostream>
#include "out/ConnectionChecker.h"
//#include "internalCounter.h" // Include the header where internalCounter is defined

using namespace std;
bool checkConnectionStatus(auto *start_time) {
    //int result = internalCounter(&start_time); 
    int result = 1;
  
    if (result == 1) {
        cout << endl;
        cout << "====================================" << endl;
        std::cout << "Connection is established." << std::endl;
        cout << "====================================" << endl;
        cout << endl;
        return true;
    }
    else {
        cout << endl;
        cout << "====================================" << endl;
        std::cout << "Connection is lost." << std::endl;
        cout << "====================================" << endl;
        cout << endl;
        return false;
    }
}
