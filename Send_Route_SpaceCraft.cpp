
#include <iostream>
#include <string>
//#include <nlohmann/json.hpp>
#include "curl.h"
#include "crow_all.h"
#include <map>

//using json = nlohmann::json;
using namespace crow;
using namespace std;


// Callback function to write response data from cURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}


void sendJsonPacketToUri(const crow::json::rvalue& jsonPacket)
{
    CURL* curl;
    CURLcode res; 

    curl = curl_easy_init();
    if (curl)
    {
        // Check if the "URI" key exists in the JSON packet
        if (jsonPacket.has("URI")) {
            // Extract the URI from the JSON packet
            const std::string& uri = jsonPacket["URI"].s();

            // Set the cURL options
            curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, NULL);

            // Convert the JSON packet back to a string for the request body
            string jsonPacketString = jsonPacket.operator std::string();
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPacketString.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonPacketString.length());

            // Response data will be stored in this string
            string response_data;

            // Set the callback function to handle the response
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

            // Perform the cURL POST request
            res = curl_easy_perform(curl);

            // Check for errors
            if (res != CURLE_OK)
            {
                std::cerr << "cURL failed: " << curl_easy_strerror(res) << std::endl;
            }
            else
            {
                cout << "Packet sent successfully to " << uri << std::endl;
                cout << "Response: " << response_data << std::endl;
            }

            // Clean up cURL
            curl_easy_cleanup(curl);
        }
        else
        {
            std::cerr << "URI not found in the JSON packet." << std::endl;
        }
    }
    else
    {
        std::cerr << "cURL initialization failed." << std::endl;
    }
}