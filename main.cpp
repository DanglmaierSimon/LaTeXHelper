#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <vector>
#include <cassert>
#include <algorithm>
#include <getopt.h>
#include <sstream>

int const flagSet = 1;

int const errUnknownArg = -1;
int const errNoError = 0;

using namespace std;


//Flags for Command line Arguments

struct flags{
	int dbgFlag;
	int stdoutFlag;
	int fileoutFlag;
	int fileNameAsCaption;
	int customCaption;
};

static flags progFlags;
static string caption;
static string language;



//TODO: Fix the values for the characters identifying the options to avoid conflicts
option static const options[] = {
		//Options that set a flag:
		{"debug",   no_argument,        &progFlags.dbgFlag,       flagSet},
		{"stdout",  no_argument,        &progFlags.stdoutFlag,    flagSet},
		{"file",    required_argument,  &progFlags.fileoutFlag,   flagSet},
		{"name-as-caption", no_argument, &progFlags.fileNameAsCaption, flagSet},



		//Options, that dont set a flag:
		{"dir",     required_argument, nullptr, 'r'},
		{"ext",     required_argument, nullptr, 'e'},
		{"caption", required_argument, nullptr, 'x'},
		{"lang",    required_argument, nullptr, 'l'},

		{nullptr, 0, nullptr, 0}
};

//Default file extensions are .h, .hpp, .c, .cpp
static vector<string> exts;

bool ScanFile(dirent* dir);
bool ScanFileExt(string const & name);
int CheckArguments(int argc, char** argv);
void PrintHelp();
void ReadDir(DIR* directory, flags const & flgs);

//Splits a string by the delimiters and stores the result in a vector, used
//to extract the extensions from the command line arguments
void SplitString(string const & str, char const & delim, vector<string> & res);

void PrintInputListing(string const & filename, flags const & flgs);
string PrintOptions(string const & fileName, flags const & flgs);



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

			case 'x':
				caption = string(optarg);
				break;

			case 'l':
				language = string(optarg);
				break;

			case '?':
				cout << "Error: Unknown argument" << endl;
				break;

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
void ReadDir(DIR* directory, flags const & flgs) {
	dirent* direntry = nullptr;

	if (directory == nullptr) {
		return;
	}

	do {
		direntry = readdir(directory);

		if (ScanFile(direntry) && ScanFileExt(string(direntry->d_name))) {
			PrintInputListing(string(direntry->d_name), flgs);
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

void PrintInputListing(string const & filename, flags const & flgs) {
	//TODO: Implement printing to file/Stdout based on the flags set, right now it just prints to stdout

	string out;

	//TODO: Finish this print
	out = "\\lstinputlisting" + PrintOptions(filename, flgs) + "{" + filename + "}";

	cout << out << endl;
}

string PrintOptions(string const & fileName,flags const & flgs) {
	string ret;
	vector<string> options;

	if (flgs.fileNameAsCaption) {
		options.push_back("caption=" + fileName);
	}
	else if (!caption.empty()) {
		options.push_back("caption=" + caption);
	}

	if (!language.empty()){
		options.push_back("language=" + language);
	}

	if (options.empty()) {
		return "";
	}
	else {
		ret += "[" + options.front();
		for (int i = 1; i < options.size(); ++i) {
			ret += ", " + options[i];
		}
	}

	return ret + "]";
}