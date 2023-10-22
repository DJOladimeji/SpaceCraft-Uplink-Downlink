#include "readFromFile.h"
#include <fstream>
#include <iostream>

using namespace std;

fileData readFromFile() {
	fileData data;
	string fileName = "ipconfig.txt";

	ifstream file(fileName);
	if (file.is_open()) {
		string line;

		while (getline(file, line)) {
			data.lines.push_back(line);
		}

		file.close();
	}
	else {
		cerr << "Unable to open file: " << fileName << endl;
	}

	return data;
} 