#include <iostream>
#include <algorithm>

#include "ReadDir.h"

using namespace std;

//local functions
//Reads one directory and returns all files matching the fileextensions
std::vector<std::string> ReadDir(std::string const & dirName);

//Appends the values of vector right to vector left and returns it
void AppendVectors(vector<string> & vecLeft, vector<string> const & vecRight);

//Prints error message to cerr
void PrintError(string const & msg);

//Scans a direntry and returns true, if its a file
bool ScanFile(dirent const * const dir);

//Scans a fil
bool ScanFileExt(string const & name);


//Lokal variables
//Vector containing the file extensions
vector<string> fileExt;

//Vector containing file paths
vector<string> paths;


void AddFileExtension(std::string const & ext) {
	fileExt.push_back(ext);
}

void AddFolderPath(std::string const & path) {
	paths.push_back(path);
}

std::vector<std::string> StartReadingDirs() {

	vector<string> res;
	for(size_t i = 0; i < paths.size(); ++i) {
		AppendVectors(res, ReadDir(paths[i]));
	}

	return res;
}

//Opens & reads the specified directory and returns any files that match the endings specified
std::vector<std::string> ReadDir(std::string const & dirName) {
	DIR* dir = opendir(dirName.c_str());
	vector<string> retVec;
	dirent* direntry;

	if(dir == nullptr) {
		PrintError("Failed to open directory!");
		return retVec;
	}

	do {
		direntry = readdir(dir);

		if(ScanFile(direntry) && ScanFileExt(string(direntry->d_name))) {
			retVec.push_back(string(direntry->d_name));
		}


	} while(direntry != nullptr);

	return retVec;
}



void PrintError(string const & msg) {
	cerr << "An error has occured!" << endl;
	cerr << "Message: " << msg << endl;
	cerr << "---------" + string(msg.length(), '-') << endl;
}


bool ScanFile(dirent const * const dir) {
	if(dir == nullptr) {
		return false;
	}
	else if(dir->d_type != DT_REG) {
		return false;
	}
	else if((dir->d_namlen) <= 2) {
		return false;
	}

	return true;
}

void AppendVectors(vector<string> & vecLeft, vector<string> const & vecRight) {
	for(size_t i = 0; i < vecRight.size(); ++i) {
		vecLeft.push_back(vecRight[i]);
	}
}

bool ScanFileExt(string const & name) {

	for(size_t i = 0; i < fileExt.size(); ++i) {
		size_t endIndex = name.size() - (fileExt[i].size() + 1);

		size_t found = name.find(fileExt[i], endIndex);

		if(found != string::npos) {
			return true;
		}
	}

	return false;
}