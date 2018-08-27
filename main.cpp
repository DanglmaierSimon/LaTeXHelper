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

struct flags{
	int dbgFlag = flagNotSet;
	int stdoutFlag = flagSet;
	int fileoutFlag = flagNotSet;
};

static flags progFlags;




option static const options[] = {
		//Options that set a flag:
		{"debug",   no_argument,        &progFlags.dbgFlag,       flagSet},
		{"stdout",  no_argument,        &progFlags.stdoutFlag,    flagSet},
		{"file",    required_argument,  &progFlags.fileoutFlag,   flagSet},


		//Options, that dont set a flag:
		{"dir",     required_argument, nullptr,  'r'},
		{"ext",     required_argument, nullptr,  'e'},

		{0, 0, 0, 0}
};

//Default file extensions are .h, .hpp, .c, .cpp
static vector<string> exts;

bool ScanFile(dirent* dir);
bool ScanFileExt(string const & name);
int CheckArguments(int argc, char** argv);
void PrintHelp();
void ReadDir(DIR* directory, flags const & flg);

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

	DIR* directory = nullptr;

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
				for (auto const & elem : exts) {
					cout << elem << endl;
				}

				break;

			case 'p':
				cout << "Option p: Print to stdout" << endl;
				//assert(stdoutFlag == flagSet);
				break;

			case 'd':
				cout << "Option d: Debug mode (verbose logging to stdout)" << endl;
				//assert(dbgFlag == flagSet);
				break;

			case 'r':
				cout << "Option r: Directory to read with argument " << optarg << endl;
				directory = opendir(optarg);

				assert(directory != nullptr);
				break;

			case '?':
				cout << "Error: Unknown argument" << endl;

			default:
				cout << "unknown error" << endl;
				return errUnknownArg;

		}
	}

	ReadDir(directory, progFlags);


	closedir(directory);

	cout << "Done!" << endl;

	return errNoError;
}

void PrintHelp(){

}


//Opens & reads the specified directory and returns any files that match the endings specified
void ReadDir(DIR* directory, flags const & flg) {
	dirent* direntry = nullptr;

	if (directory == nullptr) {
		return;
	}

	do {
		direntry = readdir(directory);

		if (ScanFile(direntry) && ScanFileExt(string(direntry->d_name))) {

			//TODO: Implement the printing to file or stdout
			if (progFlags.stdoutFlag) {
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