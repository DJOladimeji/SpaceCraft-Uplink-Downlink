#include <iostream>
#include <string>
#include <string>
#include <vector> 
#include <fstream> 

using namespace std;

struct IPADDRESSES {
	string payloadGround;
	string payloadSpace;
	string payloadCentre;
	string UplinkDownlinkGround;
	string CAndDHGround;
	string CAndDHSpacecraft;
};

void readFromFile() {
	vector<string> ipAddresses; 

	// Open the file
	ifstream file("ipconfig.txt");

	// Check if the file is opened successfully
	if (!file.is_open()) {
		cerr << "Could not open the file." << endl;
		//return 1;
	}

	// Read and print each line from the file
	string line;
	while (getline(file, line)) {
		ipAddresses.push_back(line);
		for (int i = 0; i < ipAddresses.size(); i++)
			cout << ipAddresses[i] << endl;
	}

	// Close the file
	file.close();

	IPADDRESSES IPAddresses;
	IPAddresses.payloadGround = ipAddresses[0];
	IPAddresses.payloadSpace = ipAddresses[1];
	IPAddresses.payloadCentre = ipAddresses[2];
	IPAddresses.UplinkDownlinkGround = ipAddresses[3];
	IPAddresses.CAndDHGround = ipAddresses[4];
	IPAddresses.CAndDHSpacecraft = ipAddresses[5]; 

	/* for (int i = 0; i < 6; i++) {
		cout << IPAddresses.payloadGround << endl;
		cout << IPAddresses.payloadSpace << endl;
		cout << IPAddresses.payloadCentre << endl;
		cout << IPAddresses.UplinkDownlinkGround << endl;
		cout << IPAddresses.CAndDHGround << endl;
		cout << IPAddresses.CAndDHSpacecraft << endl;
	} */

	//return 0;
} 