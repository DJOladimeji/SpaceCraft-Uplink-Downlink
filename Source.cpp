#define CROW_MAIN  

#include "crow_all.h"  
#include <iostream>

#include "readFromFile.h"
#include "Verify_Path.h"
#include <string>
#include <vector>
#include "string.h" 

#include <string>
#include <fstream>
#include <sstream>

using namespace std;
using namespace crow;

#include "Buffer.h"

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

	//the read from file object will call a methods to read the IP address from file

	//start counter 


	crow::SimpleApp app;

	CROW_ROUTE(app, "/UD_Ground_Receive").methods(HTTPMethod::Post, HTTPMethod::Get, HTTPMethod::Put)
		([](const crow::request& req, crow::response& res) {
		string post = "POST";
		string method = method_name(req.method);

		int resultPost = post.compare(method);

		if (resultPost == 0) {
			crow::json::rvalue json_data = crow::json::load(req.body);

			//check time

			//if out of time reponsed with 503
			/*
			ostringstream contents;
			res.code = 503;
			res.write(contents.str());
			*/

			//else

			if (!json_data) {
				ostringstream contents;
				res.code = 400;
				res.write(contents.str());
			}

			cout << endl;
			cout << "====================================" << endl;
			cout << "Recieved messages from Ground" << endl;
			cout << "====================================" << endl;
			cout << endl;

			//create a verify_path object
			VerifyPath verify;
			PacketData packet;
			bool verified = verify.verify(json_data, packet);
			//call a method in the object and send it the json_data to verify path

			ostringstream contents;
			res.code = 200;
			res.write(contents.str());
		}
		else {
			ostringstream contents;
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

			//check time

			//if out of time put in buffer
			/*Buffer buffer;
			buffer.add_to_Buffer(json_data);

			//respond to the C&DH
			ostringstream contents;
			res.code = 200;
			res.write(contents.str());
			*/

			//else

			if (!json_data) {
				ostringstream contents;
				res.code = 400;
				res.write(contents.str());
			}

			cout << endl;
			cout << "====================================" << endl;
			cout << "Recieved messages from C&DH" << endl;
			cout << "====================================" << endl;
			cout << endl;

			//create a verify_path object
			VerifyPath verify;
			PacketData packet;
			bool verified = verify.verify(json_data, packet);
			//call a method in the object and send it the json_data to verify path

			ostringstream contents;
			res.code = 200;
			res.write(contents.str());
		}
		else {
			ostringstream contents;
			res.code = 400;
			res.write(contents.str());

		}
		res.end();
			});

	//revieve packets from C&DH
	//if out of time send to buffer and respond with 200



	app.port(23500).multithreaded().run();
	return 1;
} 