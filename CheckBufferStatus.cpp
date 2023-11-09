#include <iostream>
#include <string>
#include "crow_all.h"

using namespace std;
struct Result
{
    string status;
    size_t elementCount;
};

Result checkJsonArrayStatus(const json& jsonArray)
{
    Result result;

    if (jsonArray.is_array())
    {
        result.elementCount = jsonArray.size();

        if (jsonArray.empty())
        {
            result.status = "JSON array is empty.";
        }
        else
        {
            result.status = "JSON array is non-empty and valid.";
        }
    }
    else {
        result.status = "Provided JSON is not an array.";
        result.elementCount = 0;
    }

    return result;
}

int source()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/BufferStatus")
        .methods("GET"_method)
        ([&](const crow::request& req)
        {

                Result result = checkJsonArrayStatus(jsonArray);

                crow::json::wvalue response;
                response["status"] = result.status;
                response["elementCount"] = result.elementCount;

                return crow::response(response);
        });

    app.port(23500).multithreaded().run();

    return 0;
}


