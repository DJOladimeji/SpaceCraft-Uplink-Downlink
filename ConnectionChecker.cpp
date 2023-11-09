#include "connection_checker.h"
#include "internalCounter.h" // Include the header where internalCounter is defined

int checkConnectionStatus() {
    int result = internalCounter();

    if (result == 1) {
        std::cout << "Connection is established." << std::endl;
    }
    else {
        std::cout << "Connection is lost." << std::endl;
    }

    return 0;
}
