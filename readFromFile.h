#ifndef FILE_READER_H 
#define FILE_READER_H 

#include <vector>
#include <string>

struct fileData {
	std::vector<std::string> lines;
};

fileData readFromFile();

#endif 