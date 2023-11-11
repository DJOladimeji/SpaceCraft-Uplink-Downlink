#define CROW_MAIN  

#include "crow_all.h"  
#include <iostream>
#include <chrono>
#include <thread>

#include "Buffer.h"
#include "out/ConnectionChecker.h"
#include "readFromFile.h"
#include "internalCounter.h" 
#include "Verify_Path.h"
#include <string>
#include <vector>
#include "string.h" 
#include "CheckBufferStatus.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;
using namespace crow;
using namespace chrono; 

//---------------------------------------makeshift timmer-----------------------------------
//set timer times
seconds duration_4_minutes(240);
seconds duration_10_minutes(600); 

//set the initial active timer 
bool is_4_minute_timer = true;

//get the currect time point
auto start_time = steady_clock::now();
//------------------------------------------------------------------------------------------

//start counter 
//auto start_Time = startCounter();
//int connection = internalCounter(start_Time);
// 
 Buffer buffer; 

int main() {
	cout << "======================================================" << endl;
	cout << "Welcome to the space Spacecrafts Uplink/Downlink" << endl;
	cout << "======================================================" << endl;


	//create a read from file object 
	fileData data = readFromFile(); 

	struct IPADDRESSES {
		string payloadGround;
		string payloadSpace;
		string payloadCentre;
		string UplinkDownlinkGround;
		string CAndDHGround;
		string CAndDHSpacecraft;
	};

	IPADDRESSES IPAddresses;

	IPAddresses.payloadGround = data.lines[0];
	IPAddresses.payloadSpace = data.lines[1];
	IPAddresses.payloadCentre = data.lines[2];
	IPAddresses.UplinkDownlinkGround = data.lines[3];
	IPAddresses.CAndDHGround = data.lines[4];
	IPAddresses.CAndDHSpacecraft = data.lines[5];

	cout << IPAddresses.payloadGround << endl;
	cout << IPAddresses.payloadSpace << endl;
	cout << IPAddresses.payloadCentre << endl;
	cout << IPAddresses.UplinkDownlinkGround << endl;
	cout << IPAddresses.CAndDHGround << endl;
	cout << IPAddresses.CAndDHSpacecraft << endl; 
	
	
	crow::SimpleApp app;

	CROW_ROUTE(app, "/UD_Ground_Receive").methods(HTTPMethod::Post, HTTPMethod::Get, HTTPMethod::Put)
		([](const crow::request& req, crow::response& res) {
		string post = "POST";
		string method = method_name(req.method);

		int resultPost = post.compare(method);
		ostringstream contents;

		if (resultPost == 0) {
			crow::json::rvalue json_data = crow::json::load(req.body);

			//check time
			auto current_time = steady_clock::now();
			auto elaspased_time = duration_cast<seconds>(current_time - start_time);
			//bool connectionstatus = checkConnectionStatus(&start_Time); 

			if (is_4_minute_timer == true && elaspased_time >= duration_4_minutes){
			//if (connectionstatus == false){
				cout << endl;
				cout << "====================================" << endl;
				cout << "4 minutes timer is up, switching to 10 minutes timer" << endl;
				cout << "No connection with the ground" << endl;
				cout << "====================================" << endl;
				cout << endl;

				//switch to 10 mintes timer 
				is_4_minute_timer = false;
				start_time = steady_clock::now(); //reset the start time;

				ostringstream contents;
				res.code = 503;
				res.write(contents.str());
			}
			else if (is_4_minute_timer == false && elaspased_time >= duration_10_minutes){
			//else {
				cout << endl;
				cout << "====================================" << endl;
				cout << "10 minute timer expired, switching to 4 minutes" << endl;
				cout << "====================================" << endl;
				cout << endl;

				//switching to to 4 minutes timer
				is_4_minute_timer = true;
				start_time = steady_clock::now();
			}

			else if(is_4_minute_timer == true && elaspased_time <= duration_4_minutes){  
				cout << endl;
				cout << "====================================" << endl;
				cout << "Recieved messages from Ground" << endl;
				cout << "====================================" << endl;
				cout << endl;

				if (!json_data) {
					cout << endl;
					cout << "====================================" << endl;
					cout << "No json data attached to the payload from the ground" << endl;
					cout << "====================================" << endl;
					cout << endl;


					res.code = 400;
					res.write(contents.str());
					res.end();
				}

				//create a verify_path object
				VerifyPath verify;
				PacketData packet;
				bool verified = verify.verify(json_data, packet);
				//call a method in the object and send it the json_data to verify path

				//if false return 503 error code 
				if (verified == false) {
					res.code = 503;
					res.write(contents.str());
					res.end();
				}
				else {
					ostringstream contents;
					res.code = 200;
					res.write(contents.str());
				}
			}
		}
		else {
			cout << endl;
			cout << "====================================" << endl;
			cout << "Didn't Recieve a POST request from the Ground Uplink/Downlink" << endl;
			cout << "====================================" << endl;
			cout << endl;

			res.code = 400;
			res.write(contents.str());
		}
		res.end();
			});

	//recieve Packets from the C&DH
	CROW_ROUTE(app, "/C&DH_Receive").methods(HTTPMethod::Post, HTTPMethod::Get, HTTPMethod::Put)
		([](const crow::request& req, crow::response& res) {
		string post = "POST";
		string method = method_name(req.method);

		int resultPost = post.compare(method);

		if (resultPost == 0) {
			crow::json::rvalue json_data = crow::json::load(req.body);
			cout << endl;
			cout << "====================================" << endl;
			cout << "Recieved messages from C&DH" << endl;
			cout << "====================================" << endl;
			cout << endl;


			//check time
			auto current_time = steady_clock::now();
			auto elaspased_time = duration_cast<seconds>(current_time - start_time);
			//bool connectionStatus = checkConnectionStatus(&start_Time);

			//if out of time
			if (is_4_minute_timer && elaspased_time >= duration_4_minutes){
			//if(connectionStatus == false){
				cout << endl;
				cout << "====================================" << endl;
				cout << "4 minutes timer is up, switching to 10 minutes timer" << endl;
				cout << "No connection with the ground" << endl;
				cout << "====================================" << endl;
				cout << endl;

				//switch to 10 mintes timer 
				is_4_minute_timer = false;
				start_time = steady_clock::now(); //reset the start time;

				crow::json::rvalue json_data = crow::json::load(req.body);   
				buffer.add_to_Buffer(json_data);  

				cout << endl;
				cout << "====================================" << endl;
				cout << "No Connection Added message to buffer" << endl;
				cout << "====================================" << endl;
				cout << endl;

				//respond to the C&DH 
				ostringstream contents; 
				res.code = 200; 
				res.write(contents.str()); 
				res.end();
					
			}
			else if (!is_4_minute_timer && elaspased_time >= duration_10_minutes){
			//else{
				cout << endl;
				cout << "====================================" << endl;
				cout << "10 minute timer expired, switching to 4 minutes" << endl;
				cout << "====================================" << endl;
				cout << endl;

				//switching to to 4 minutes timer
				is_4_minute_timer = true;
				start_time = steady_clock::now();
			}

			else if (is_4_minute_timer == true && elaspased_time <= duration_4_minutes) {
				if (!json_data) {
					cout << endl;
					cout << "====================================" << endl;
					cout << "No json data added to the body of the data received from C&DH" << endl;
					cout << "====================================" << endl;
					cout << endl;
					ostringstream contents;
					res.code = 400;
					res.write(contents.str());
					res.end();
				}
				else {
					//create a verify_path object
					VerifyPath verify;
					PacketData packet;
					bool verified = verify.verify(json_data, packet);
					//call a method in the object and send it the json_data to verify path

					ostringstream contents;
					res.code = 200;
					res.write(contents.str());
				}
			}

			else if (!is_4_minute_timer == true && elaspased_time <= duration_10_minutes) {
				if (!json_data) {
					cout << endl;
					cout << "====================================" << endl;
					cout << "No json data added to the body of the data received from C&DH" << endl;
					cout << "====================================" << endl;
					cout << endl;
					ostringstream contents;
					res.code = 400;
					res.write(contents.str());
					res.end();
				}

				crow::json::rvalue json_data = crow::json::load(req.body);
				buffer.add_to_Buffer(json_data);

				cout << endl;
				cout << "====================================" << endl;
				cout << "No Connection Added message to buffer" << endl;
				cout << "====================================" << endl;
				cout << endl;

				//respond to the C&DH 
				ostringstream contents;
				res.code = 200;
				res.write(contents.str());
				res.end();
			}
		}
		else {
			cout << endl;
			cout << "====================================" << endl;
			cout << "Didn't recieve A POST request from the C&DH" << endl;
			cout << "====================================" << endl;
			cout << endl;

			ostringstream contents;
			res.code = 400;
			res.write(contents.str());

		}
		res.end();
			});

	CROW_ROUTE(app, "/GroundConnection")
		.methods("GET"_method)
		([&](const crow::request& req)
			{
				cout << endl;
				cout << "====================================" << endl;
				cout << "C&DH Request Ground status" << endl;
				cout << "====================================" << endl;
				cout << endl;

				crow::json::wvalue response; 

				if (is_4_minute_timer)
				{
					response["status"] = "Connection is established.";
				}
				else
				{
					response["status"] = "Connection is lost.";
				}

				return crow::response(response);
		});

	CROW_ROUTE(app, "/BufferStatus")
		.methods("GET"_method)
		([&](const crow::request& req)
			{
				cout << endl;
				cout << "====================================" << endl;
				cout << "C&DH request Buffer status" << endl;
				cout << "====================================" << endl;
				cout << endl;

				Result result = checkJsonArrayStatus(buffer);

				crow::json::wvalue response; 
				response["status"] = result.status;

				return crow::response(response);
			});

	app.port(8080).multithreaded().run();
	return 1;
} 

