// Finding out where the packet will be going and send to the correct route class (ground or spacecraft)

#include "verify_path.h"  // Including the header file for verify_path

// Definining a function to verify the path and store packet data
bool VerifyPath::verify(const crow::json::rvalue& json_data, PacketData& packet) {
    // Checking if the "URI" and "method" fields exist in the JSON data
    /*if (json_data.has("URI") && json_data["URI"].t() == crow::json::type::String &&
        json_data.has("route") && json_data["route"].t() == crow::json::type::String) {
        packet.uri = json_data["URI"].s();
        packet.method = json_data["route"].s();

        // Extracting and storing the path from the URI
        size_t uriPathDelimiter = packet.uri.find('?');
        if (uriPathDelimiter != std::string::npos) {
            packet.path = packet.uri.substr(0, uriPathDelimiter);
        }
        else {
            packet.path = packet.uri;
        }

        // Checking the URI and request method to distinguish between sources
        if (packet.uri == "/UD_Ground_Recieve") {
            // This packet is from ground uplink/downlink
            if (packet.method == "POST" || packet.method == "PUT") {
                packet.json_data = json_data; // Storing the JSON data
                return true;
            }
        }
        else if (packet.uri == "/C_and_DH_Recieve") {
            // This packet is from spacecraft C&DH
            if (packet.method == "GET") {
                packet.json_data = json_data; // Storing the JSON data
                return true;
            }
        }
    }

    return false;  // Path is not valid or from an unrecognized source*/

    string verb = json_data["Verb"].s();

    if (verb == "POST"|| verb == "PUT"|| verb == "GET") {
        return true;
    }
    else {
        cout << endl;
        cout << "====================================" << endl;
        cout << "Data in verb place: " << verb << endl;
        cout << "====================================" << endl;
        cout << endl;
        return false;
    }
}
