#include "Send_Route_SpaceCraft.h"


int createSocketAndConnect_SpaceCraft(char* host, int port) 
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Error creating socket");
        return -1;
    }

    struct hostent* server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr, "Error: No such host\n");
        close(clientSocket);
        return -1;
    }

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    memcpy(&serverAddress.sin_addr.s_addr, server->h_addr, server->h_length);
    serverAddress.sin_port = htons(port);

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error connecting to server");
        close(clientSocket);
        return -1;
    }

    return clientSocket;
}


char* SendToSpaceCraft(crow::json::rvalue json_data, int port) 
    {
        port = 8080;
        const char* prefix = "http://";
        char* host = nullptr;
        const char* path = "/";

        std::string tempurl; 
        std::string tempverb; 

        try 
        {
            tempurl = json_data["url"].s(); 
            tempverb = json_data["verb"].s(); 
        }
        catch (const std::exception& e) 
        {
            std::cerr << "Error extracting URL from JSON: " << e.what() << std::endl;
            return nullptr;
        }

        const char* url = tempurl.c_str();
        const char* verb = tempverb.c_str();

        std::string fullPath = url;
        const char* Route = fullPath.c_str();

        char* urlCopy = strdup(Route);
        char* token = strtok(urlCopy, "/");
        if (token && strcmp(token, "http:") == 0) {
            token = strtok(NULL, "/");
        }

        if (token) {
            host = token;
            token = strtok(NULL, "");
            if (token) {
                path = token;
            }
        }

        token = strchr(host, ':');
        if (token) {
            *token = '\0';
            port = atoi(token + 1);
        }

        free(urlCopy);

        int clientSocket = createSocketAndConnect_SpaceCraft(host, port); 
        if (clientSocket < 0) {
            return nullptr;
        }

        /*string coordinateX = json_data["coordinate"]["x"].s();
        string coordinateY = json_data["coordinate"]["y"].s();
        string coordinateZ = json_data["coordinate"]["z"].s();
        string rotationP = json_data["rotation"]["p"].s();
        string rotationY = json_data["rotation"]["y"].s();
        string rotationR = json_data["rotation"]["r"].s();*/

        //crow::json::rvalue payload;

        

        /*try {
            /*payload["coordinate"]["x"] = json_data["coordinate"]["x"].s();
            payload["coordinate"]["y"] = json_data["coordinate"]["y"].s();
            payload["coordinate"]["z"] = json_data["coordinate"]["z"].s();
            payload["rotation"]["p"] = json_data["rotation"]["p"].s(); 
            payload["rotation"]["y"] = json_data["rotation"]["y"].s();
            payload["rotation"]["r"] = json_data["rotation"]["r"].s();
        }
        catch (const std::exception& e) {
            std::cerr << "Error extracting values from JSON: " << e.what() << std::endl;
            close(clientSocket);
            return nullptr;
        }*/

        std::ostringstream oss;
        oss << json_data; 
        std::string json_payload = oss.str();


    char request[1000];
    sprintf(request, "%s %s HTTP/1.1\r\nHost: %s\r\nContent-Type: application/json\r\nContent-Length: %zu\r\nConnection: close\r\n\r\n%s", verb, path, host, json_payload.length(), json_payload.c_str());

    if (send(clientSocket, request, strlen(request), 0) < 0) 
    {
        perror("Error sending space craft request");
        close(clientSocket);
        return NULL;
    }

    char response[4096];
    char* fullResponse = NULL;
    ssize_t bytesRead;
    size_t totalBytesRead = 0;

    while ((bytesRead = recv(clientSocket, response, 4096 - 1, 0)) > 0) 
    {
        response[bytesRead] = '\0';
        if (fullResponse == NULL) 
        {
            fullResponse = strdup(response);
        }
        else 
        {
            strcat(fullResponse, response);
        }
        totalBytesRead += bytesRead;
    }

    close(clientSocket);

    cout << fullResponse << endl;

    return fullResponse;
}