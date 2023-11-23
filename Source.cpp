#define CROW_MAIN  

#include "crow_all.h"  
#include <iostream>
#include <chrono>
#include <thread>

#include "Buffer.h"
#include "readFromFile.h"
#include "internalCounter.h" 
#include "Verify_Path.h"
#include <string>
#include <vector>
#include "string.h" 
#include "CheckBufferStatus.h"
#include "Send_Route_Ground.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;
using namespace crow;
using namespace chrono; 

//---------------------------------------timmer-----------------------------------
//set timer times
seconds duration_4_minutes(240);
seconds duration_10_minutes(600); 

//set the initial active timer 
bool is_4_minute_timer = true;

//get the currect time point
auto start_time = steady_clock::now();

//------------------------------------------------------------------------------------------

 Buffer buffer; //buffer to store request when there is no connction with the ground 

 int checkConnection() { // function to check timer 
	 seconds four_minutes(240);
	 seconds ten_minutes(600);
	 auto current_time = steady_clock::now();
	 auto elaspased_time = duration_cast<seconds>(current_time - start_time);

	 if (is_4_minute_timer == true && elaspased_time >= four_minutes) {
		 is_4_minute_timer = false;
		 start_time = steady_clock::now();

		 cout << endl;
		 cout << "====================================" << endl;
		 cout << "4 minutes timer is up, switching to 10 minutes timer" << endl;
		 cout << "No connection with the Ground" << endl;
		 cout << "====================================" << endl;
		 cout << endl;

		 return 0;
	 }

	 else if (is_4_minute_timer == false && elaspased_time >= ten_minutes) {
		 is_4_minute_timer = true;
		 start_time = steady_clock::now();

		 cout << endl;
		 cout << "====================================" << endl;
		 cout << "10 minute timer expired, switching to 4 minutes" << endl;
		 cout << "====================================" << endl;
		 cout << endl;

		 vector<crow::json::rvalue> buffered_messages;
		 int buffer_size = buffer.Buffer_size();

		 if (buffer_size != 0) {
			 buffered_messages = buffer.remove_from_buffer();

			 for (int i = 0; i < buffered_messages.size(); i++) {
				 sendtoGround(buffered_messages[i], 8080);
			 }

			 return 1;
		 }
		 else {
			 return 1;
		 }
	 }

	 else if (is_4_minute_timer == true && elaspased_time <= four_minutes) {

		 cout << endl;
		 cout << "====================================" << endl;
		 cout << "There is connection with the Ground " << endl;
		 cout << "====================================" << endl;
		 cout << endl;

		 return 2;
	 }

	 else if (is_4_minute_timer == false && elaspased_time <= ten_minutes) {

		 cout << endl;
		 cout << "====================================" << endl;
		 cout << "No connection with ground in 10 minute section" << endl;
		 cout << "====================================" << endl;
		 cout << endl;

		 return 3;
	 }

	 else {
		 cout << endl;
		 cout << "====================================" << endl;
		 cout << "Error in checking timer" << endl;
		 cout << "====================================" << endl;
		 cout << endl;

		 return 4;
	 }
 }

 
int main() {
	cout << "======================================================" << endl;
	cout << "Welcome to the space Spacecrafts Uplink/Downlink" << endl;
	cout << "======================================================" << endl;


	//create a read from file object 
	IPADDRESSES ipaddress = readFromFile();  
	cout << "Read from file" << endl;
	
	crow::SimpleApp app;

	CROW_ROUTE(app, "/UD_Ground_Receive").methods(HTTPMethod::Post, HTTPMethod::Get, HTTPMethod::Put)
		([](const crow::request& req, crow::response& res) {
		string post = "POST";
		string method = method_name(req.method);

		int resultPost = post.compare(method);
		ostringstream contents;

		if (resultPost == 0) {
			crow::json::rvalue json_data = crow::json::load(req.body);

			cout << endl;
			cout << "====================================" << endl;
			cout << "Recieved Message from the ground" << endl;
			cout << "====================================" << endl;
			cout << endl;

			int connectionstatus = checkConnection();

			if (connectionstatus == 0){  
				ostringstream contents;
				res.code = 503;
				res.write(contents.str());
			}
			else if (connectionstatus == 1){

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
			else if(connectionstatus == 2){
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

				//if false return 503 error code 
				if (verified == false) {
					cout << endl;
					cout << "====================================" << endl;
					cout << "Verification of Message failed" << endl;
					cout << "====================================" << endl;
					cout << endl;

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
			else if (connectionstatus == 3) {
				ostringstream contents; 
				res.code = 503; 
				res.write(contents.str());  
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

		VerifyPath verify; 
		PacketData packet;  

		if (resultPost == 0) {
			crow::json::rvalue json_data = crow::json::load(req.body);
			cout << endl;
			cout << "====================================" << endl;
			cout << "Recieved messages from C&DH" << endl;
			cout << "====================================" << endl;
			cout << endl;

			//check time
			int connectionStatus = checkConnection();
			
			if(connectionStatus == 0){ 
				crow::json::rvalue json_data = crow::json::load(req.body);    
				buffer.add_to_Buffer(json_data);   

				cout << endl;
				cout << "====================================" << endl;
				cout << "No Connection" << endl << "Added message to buffer" << endl; 
				cout << "====================================" << endl;
				cout << endl;

				//respond to the C&DH 
				ostringstream contents; 
				res.code = 200; 
				res.write(contents.str()); 
				res.end();
					
			}
			else if (connectionStatus == 1){
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
					bool verified = verify.verify(json_data, packet);
					

					if (verified == true) {
						cout << endl;
						cout << "====================================" << endl;
						cout << "Messages verfied" << endl;
						cout << "====================================" << endl;
						cout << endl;

						sendtoGround(json_data, 8080); 

						ostringstream contents;
						res.code = 200;
						res.write(contents.str());
					}
					else{
						cout << endl;
						cout << "====================================" << endl;
						cout << "Verification of Message failed" << endl;
						cout << "====================================" << endl;
						cout << endl;

						ostringstream contents;
						res.code = 400;
						res.write(contents.str());
						res.end();
					}
				}
			}
			else if (connectionStatus == 2) {
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
					bool verified = verify.verify(json_data, packet); 
					//verified = true;
					if (verified == true) {
						cout << endl;
						cout << "====================================" << endl;
						cout << "Messages verfied" << endl;
						cout << "====================================" << endl;
						cout << endl;

						sendtoGround(json_data, 8080);

						ostringstream contents;
						res.code = 200;
						res.write(contents.str());
					}
					else {
						cout << endl;
						cout << "====================================" << endl;
						cout << "Verification of Message failed" << endl;
						cout << "====================================" << endl;
						cout << endl;

						ostringstream contents;
						res.code = 400;
						res.write(contents.str());
						res.end();
					}
				}
			}
			else if(connectionStatus == 3) {
				//create a verify_path object
				VerifyPath verify;
				PacketData packet;
				bool verified = verify.verify(json_data, packet);

				ostringstream contents;
				res.code = 200;
				res.write(contents.str());
			}

			//else if (!is_4_minute_timer == true && elaspased_time <= duration_10_minutes) {
			else if (connectionStatus == 3){
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
					response["status"] = "true";
				}
				else
				{
					response["status"] = "false";
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

