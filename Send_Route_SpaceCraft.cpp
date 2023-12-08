#include "Send_Route_SpaceCraft.h"


int createSocketAndConnect_SpaceCraft(string host, int port) 
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Error creating socket");
        return -1;
    }

    const char* temphost = host.c_str();
    struct hostent* server = gethostbyname(temphost); 
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
        char* host = NULL;
        const char* path; 

        std::string tempurl;
        std::string temp;
        std::string tempverb; 
        std::string temppath;
        std::string http;
        std::string IP;
        std::string eightyeighty;

        string tempstorage; 

        try 
        {
            temp = json_data["url"].s();
            istringstream streamline(temp);

            getline(streamline, http, ':'); 
            http += ":";
            getline(streamline, IP, ':'); 
            IP += ":";
            getline(streamline, eightyeighty, '/'); 
    
            tempurl += http; 
            tempurl += IP;
            tempurl += eightyeighty; 

            getline(streamline, temppath);   
            string start = "/";
            start += temppath; 
            path = start.c_str();     

            tempstorage = path;   

            tempverb = json_data["verb"].s(); 
            cout << "Temp verb: " << tempverb << endl;
            cout << "Pre Path: " << path << endl; 
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

        std::string tempHost = std::string(host);

        free(urlCopy);

        int clientSocket = createSocketAndConnect_SpaceCraft(tempHost, port);  
        if (clientSocket < 0) {
            return nullptr;
        }

        std::ostringstream oss;
        oss << json_data; 
        std::string json_payload = oss.str();

        cout << "verb: " << verb <<  endl;
        cout << "url: " << tempurl << endl;
        path = tempstorage.c_str(); 
        cout << "path: " << path << endl;


    char request[1000];
    sprintf(request, "%s %s HTTP/1.1\r\nHost: %s\r\nContent-Type: application/json\r\nContent-Length: %zu\r\nConnection: close\r\n\r\n%s", verb, path, host, json_payload.length(), json_payload.c_str());
    cout << endl;
    cout << "====================================" << endl;
    cout << "Message sent to subsystem" << endl;
    cout << "====================================" << endl;
    cout << endl;

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