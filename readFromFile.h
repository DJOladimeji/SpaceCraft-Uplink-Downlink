#ifndef FILE_READER_H 
#define FILE_READER_H 

#include <vector>
#include <string>

struct fileData {
	std::vector<std::string> lines;
};

struct IPADDRESSES { 
	string CAndDHGround;			//Service 1 
	string payloadCentre;			//Service 2 
	string CAndDHSpacecraft;		//Service 3 
	string UplinkDownlinkGround;	//Service 4 
	string payloadSpace;			//Service 5 
	string payloadGround;			//Service 6 
};

IPADDRESSES readFromFile(); 

#endif 