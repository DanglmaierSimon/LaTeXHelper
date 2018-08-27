#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <vector>
#include <cassert>
#include <algorithm>
#include <getopt.h>
#include <sstream>

int const flagSet = 1;
int const flagNotSet = 0;

int const errUnknownArg = -1;
int const errNoError = 0;

using namespace std;


//Flags for Command line Arguments
static int dbgFlag = flagNotSet;
static int stdoutFlag = flagSet;
static int fileoutFlag = flagNotSet;



option static const options[] = {
		//Options that set a flag:
		{"debug",   no_argument,        &dbgFlag,       flagSet},
		{"stdout",  no_argument,        &stdoutFlag,    flagSet},
		{"file",    required_argument,  &fileoutFlag,   flagSet},


		//Options, that dont set a flag:
		{"dir",     required_argument,  0,  'r'},
		{"ext",     required_argument,  0,  'e'},

		{0, 0, 0, 0}
};

//Default file extensions are .h, .hpp, .c, .cpp
static vector<string> exts;






/*

int main() {
	string dirPath;
	vector<string> files;

	cout << "Please enter name of the directory." << endl;
	cin >> dirPath;

	cout << "Path: " << dirPath << endl;;

	#pragma TODO("Ask user for additional paths")
	AddFolderPath(dirPath);

	#pragma TODO("Ask user for additional file extensions")
	AddFileExtension("c");
	AddFileExtension("cpp");
	AddFileExtension("h");



	files = StartReadingDirs();

	for(size_t i = 0; i < files.size(); ++i) {
		cout << files[i] << endl;
	}

	PrintToConsole(files);


	cout << "Press a button to continue..." << endl;
	cin.get();

	return 0;
}

 */


bool ScanFile(dirent* dir);
bool ScanFileExt(string const & name);
int CheckArguments(int argc, char** argv);
void PrintHelp();
void ReadDir(DIR* directory, bool stdOutFlag = false);

//Splits a string by the delimiters and stores the result in a vector, used
//to extract the extensions from the command line arguments
void SplitString(string const & str, char const & delim, vector<string> & res);





int main(int argc, char** argv) {
	cout << "Starting!" << endl;

	CheckArguments(argc, argv);


	return 0;
}

int CheckArguments(int argc, char** argv) {
	int optIdx;
	int opt;

	DIR* directory;
	dirent* dirptr = nullptr;

	//acceptable arguments:
	//p: print to stdout
	//d: debug mode, verbose logging to stdout
	while ((opt = getopt_long(argc, argv, "pdo:", options, &optIdx)) != -1) {

		switch (opt) {
			case 0:
				cout << "Option: " << options[optIdx].name;
				if (optarg) {
					cout << " with argument " << optarg;
				}
				cout << endl;
				break;

			case 'o':
				cout << "Option o: Output to File with argument " << optarg << endl;
				break;

			case 'e':
				cout << "Option e: Extensions with argument " << optarg << endl;
				SplitString(string(optarg), ';', exts);

				cout << "Listing extracted extensions: " << endl;
				for (auto elem : exts) {
					cout << elem << endl;
				}

				break;

			case 'p':
				cout << "Option p: Print to stdout" << endl;
				assert(stdoutFlag == flagSet);
				break;

			case 'd':
				cout << "Option d: Debug mode (verbose logging to stdout)" << endl;
				assert(dbgFlag == flagSet);
				break;

			case 'r':
				cout << "Option r: Directory to read with argument " << optarg << endl;
				directory = opendir(optarg);

				assert(directory != nullptr);
				break;

			case '?':
				cout << "Error: Unknown argument" << endl;

				return errUnknownArg;

		}
	}

	ReadDir(directory, stdoutFlag);


	closedir(directory);

	cout << "Done!" << endl;

	return errNoError;
}

void PrintHelp(){

}


//Opens & reads the specified directory and returns any files that match the endings specified
void ReadDir(DIR* directory, bool stdOutFlag) {
	dirent* direntry;

	if (directory == nullptr) {
		return;
	}

	do {
		direntry = readdir(directory);

		if (ScanFile(direntry) && ScanFileExt(string(direntry->d_name))) {

			//TODO: Implement the printing to file or stdout
			if (stdoutFlag) {
				cout << "Found a file with matching extension: " << endl;
				cout << direntry->d_name << endl;
			}
		}


	} while (direntry != nullptr);
}

bool ScanFileExt(string const & name) {
	size_t endIndex = name.find_last_of('.');

	if (endIndex == string::npos) {
		return false;
	}

	string fileExt{name, endIndex, name.size()};

	return (find(exts.cbegin(), exts.cend(), fileExt) != exts.cend());
}

bool ScanFile(dirent* dir) {
	if (dir == nullptr) {
		return false;
	} else if (dir->d_type != DT_REG) {
		return false;
	} else if (string{dir->d_name}.size() <= 2) {
		return false;
	}

	return true;
}

void SplitString(string const & str, char const & delim, vector<string> & res) {
	stringstream ss(str);
	string ext;

	while (getline(ss, ext, delim)) {
		if (!ext.empty()) {
			res.push_back('.' + ext);
		}
	}

}