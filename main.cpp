#include <iostream>
#include <string>
#include <conio.h>


#include "Hlp.h"
#include "Printer.h"
#include "ReadDir.h"

using namespace std;



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
	AddFileExtension(".cpp");
	AddFileExtension(".h");



	files = StartReadingDirs();

	for(size_t i = 0; i < files.size(); ++i) {
		cout << files[i] << endl;
	}

	PrintToConsole(files);


	cout << "Press a button to continue..." << endl;
	_getch();

	return 0;
}