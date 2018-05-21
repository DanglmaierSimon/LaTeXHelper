#include <iostream>

#include "Printer.h"

using namespace std;

void PrintOptions(string const & opt);


void PrintTitle(string const & title);

void PrintFileName(string const & file);


void PrintToConsole(std::vector<std::string> const & vec) {
	for(size_t i = 0; i < vec.size(); ++i) {
		cout << "\\lstinputlisting";

		#pragma TODO("add more options here")

		PrintOptions(vec[i]);
		PrintFileName(vec[i]);
		cout << endl;
	}
}

void PrintOptions(string const & opt) {
	cout << "[title=" << opt << "]";
}

void PrintTitle(string const & title) {
}

void PrintFileName(string const & file) {
	cout << "{" << file << "}";
}
