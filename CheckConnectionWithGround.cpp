//Dummy file

/*#include <iostream>
#include <string>
#include "crow_all.h"
#include "connection_checker.h"

using namespace std;
int source()
{
    CROW_ROUTE(app, "/GroundConnection")
        .methods("GET"_method)
        ([&](const crow::request& req)
        {
                bool connectionStatus = checkConnectionStatus();

                crow::json::wvalue response;

                if (connectionStatus)
                {
                    response["status"] = "Connection is established.";
                }
                else
                {
                    response["status"] = "Connection is lost.";
                }

                return crow::response(response);
        });
}*/
