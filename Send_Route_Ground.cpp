
#include "Send_Route_Ground.h"
 

int createSocketAndConnect(char* host, int port) { 
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

char* sendtoGround(crow::json::rvalue json_data, int port) { 
    port = 8080;
    const char *prefix = "http://";
    char *host = NULL;
    const char* path = "/receive/";
 
	std::string fullPath = "http://10.144.96.96:8080"; 

    const char* Route = fullPath.c_str();

    char* url = strdup(Route);
    char* token = strtok(url, "/");
    if (token && strcmp(token, "http:") == 0) {
        //skip the http: part
        token = strtok(NULL, "/");
    }

    if (token) {
        host = token;
        token = strtok(NULL, "");
        if (token) {
            path = token;
        }
    }

    //find port number in host string 
    token = strchr(host, ':');
    if (token) {
        *token = '\0';
        port = atoi(token + 1);
    }

    int clientSocket = createSocketAndConnect(host, port); 
    free(url);

    if (clientSocket < 0) {
        return NULL;
    }

    std::ostringstream oss;  
    oss << json_data;   
    std::string json_payload = oss.str();  

    char request[1000];
    sprintf(request, "POST %s HTTP/1.1\r\nHost: %s\r\nContent-Type: application/json\r\nContent-Length: %zu\r\nConnection: close\r\n\r\n%s", path, host, json_payload.length(), json_payload.c_str());

    if (send(clientSocket, request, strlen(request), 0) < 0) { 
        perror("Error sending Ground request"); 
        close(clientSocket);
        return NULL;
    }

    cout << endl;
    cout << "====================================" << endl;
    cout << "Messages sent to ground" << endl;
    cout << "====================================" << endl;
    cout << endl;

    char response[4096]; 
    char* fullResponse = NULL; 
    ssize_t bytesRead; 
    size_t totalBytesRead = 0;  

    while ((bytesRead = recv(clientSocket, response, 4096 - 1, 0)) > 0) { 
        response[bytesRead] = '\0'; 
        if (fullResponse == NULL) { 
            fullResponse = strdup(response); 
        } 
        else { 
            //fullResponse = realloc(fullResponse, totalBytesRead + bytesRead + 1); 
            //realloc(fullResponse, totalBytesRead + bytesRead + 1); 
            strcat(fullResponse, response); 
        }
        totalBytesRead += bytesRead; 
    }

    close(clientSocket); 

    cout << fullResponse << endl; 

    return fullResponse; 
} 
