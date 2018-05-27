#include <iostream>
#include <string>
#include <libclipboard.h>

#include "Printer.h"
#include "ReadDir.h"

using namespace std;



int main() {
	string dirPath;
	vector<string> files;
	clipboard_c *cb = clipboard_new(NULL);
	char *some_text_from_clipboard = clipboard_text(cb);

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

	//PrintToConsole(files);
    std::string tString = PrintToString(files);
    std::cout << tString;
    clipboard_set_text(cb, tString.c_str());
    

	cout << "Press a button to continue..." << endl;
	getchar();
	cin.get(); // idk else it won't work
	//system("pause");
	

	return 0;
}
