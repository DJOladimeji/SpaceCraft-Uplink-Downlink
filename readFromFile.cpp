#include "readFromFile.h"
#include <fstream>
#include <iostream>

using namespace std;

IPADDRESSES readFromFile() {
	fileData data; 
	IPADDRESSES IPAddresses; 
	string fileName = "ipconfig.txt";

	ifstream file(fileName);
	if (file.is_open()) {
		string line;

		while (getline(file, line)) {
			data.lines.push_back(line);
		}

		file.close(); 


		IPAddresses.CAndDHSpacecraft = data.lines[0];
		IPAddresses.payloadSpace = data.lines[1];
		IPAddresses.UplinkDownlinkGround = data.lines[2];
		IPAddresses.CAndDHGround = data.lines[3];
		IPAddresses.payloadGround = data.lines[4];
		IPAddresses.payloadCentre = data.lines[5]; 
	}
	else {
		cerr << "Unable to open file: " << fileName << endl;
	}

	return IPAddresses; 
} 