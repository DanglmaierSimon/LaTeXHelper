#ifndef HLP_Included
#define HLP_Included

// -----------------------------------------------------
// Simple Helper Class
// This works as a repository for some useful functions.
// As this are static methods no object need to be created.
// HSD / FH-Hagenberg
//
// Usage: (1) copy Hlp.h and Hlp.cpp to your project
//        (2) #include "Hlp.h"
//        (3) call the method like:  Hlp::Method(..);
// -----------------------------------------------------

#include <string>
#include <windows.h>

class Hlp {
	Hlp();
	Hlp(Hlp const &);
	Hlp& operator = (Hlp const &);

public:

// -----------------------------------------------------------
// print a windows error as human readable string
// usage:  cout << "Error: " << Hlp::ErrMsg(GetLastError()) << endl;
static std::string ErrMsg(DWORD LastError);

};


// ---------------------------------------------------------------------------------
// With this pragma you can mark positions in your code where you have to do something.
// On each Rebuild-All your compiler will remind you about them (ouput window).
// Simple double-click on the generated warnings and you are back at the position.
//
// Usage: #pragma TODO(Fehlerbehandlung einfügen!)

#define todo_impl2(CodeLine) #CodeLine
#define todo_impl(CodeLine)  todo_impl2(CodeLine)
#define TODO(msg) message(__FILE__ "(" todo_impl(__LINE__) "): Warning TODO: " #msg)


#endif