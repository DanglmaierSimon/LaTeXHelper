#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <vector>
#include <cassert>
#include <getopt.h>

int const flagSet = 1;
int const flagNotSet = 0;

using namespace std;


//Flags for Command line Arguments
static int dbgFlag = flagNotSet;
static int stdoutFlag = flagSet;
static int fileoutFlag = flagNotSet;



option static const options[] = {
		{"dir", required_argument, 0, 0},
		{"debug", no_argument,0,0},
		{"stdout", no_argument, 0, 0},
		{"file", required_argument, 0, 0},
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
void CheckArguments(int argc, char** argv);
void PrintHelp();
void ReadDir(std::string const & dirName);





int main(int argc, char** argv){
    cout << "Starting!" << endl;

    CheckArguments(argc, argv);




	return 0;
}

void CheckArguments(int argc, char** argv) {
    int indexptr;
    /*
    //acceptable arguments:
    //p: print to stdout
    //o: print to file
    //d: debug mode, verbose logging to stdout
    //while(//(c = getopt_long(argc, argv, options,"po:")) != -1){
    switch (c) {
        case 'p':
            break;
        case 'o':
            break;
        case '?':
            break;
        default:
            cerr << "ERROR: FATAL ERROR" << endl;
            exit(-1);
    }

     */

    while (getopt_long(argc, argv, "po:", options, &indexptr) != -1){

    }

    //assert(argc == 3);
    //assert(argv[2] != nullptr);

    cout << "Arguments:"<<endl;

    for(int i = 0; i < argc; i++){
        cout << "argv[" << i << "]: " << argv[i] << endl;
    }


    auto directory = opendir(argv[2]);
    dirent* dirptr = nullptr;

    assert(directory != nullptr);


    cout << "Listing files: "<<endl;
    while(directory){
        errno = 0;

        if((dirptr = readdir(directory)) != nullptr){
            cout << dirptr->d_name<<endl;
        }
        else{
            break;
        }
    }

    ReadDir(argv[2]);


    closedir(directory);

    cout << "Done!"<<endl;




}

void PrintHelp(){

}


//Opens & reads the specified directory and returns any files that match the endings specified
void ReadDir(std::string const & dirName) {
    DIR* dir = opendir(dirName.c_str());
    dirent* direntry;

    if(dir == nullptr) {
        return;
    }

    do {
        direntry = readdir(dir);

        if(ScanFile(direntry) && ScanFileExt(string(direntry->d_name))) {
            //TODO: Implement the printing to file or stdout
            cout << "Found a file: "<<endl;
            cout << direntry->d_name << endl;
        }


    } while(direntry != nullptr);
}

bool ScanFileExt(string const & name) {

    for(size_t i = 0; i < exts.size(); i++) {
        size_t endIndex = name.find_last_of('.');

        if(endIndex == string::npos){
            return false;
        }
        string fileExt{name, endIndex, name.size()};

        return (fileExt == exts[i]);
    }

    return false;
}

bool ScanFile(dirent* dir) {
    if(dir == nullptr) {
        return false;
    }
    else if(dir->d_type != DT_REG) {
        return false;
    }
    else if((std::char_traits<char>::length(dir->d_name)) <= 2) {
        return false;
    }

    return true;
}
