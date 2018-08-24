//MIP
#ifndef READDIR_H
#define READDIR_H
//test comments


//---------------
//System Includes
//---------------
#include <string>
#include <vector>

//Add a file extension to be considered
//The file extension should be entered without the Dot
//Ex: if you want .h and .cpp files, just enter h and cpp
void AddFileExtension(std::string const & ext);

//Add a path to a folder to search for
void AddFolderPath(std::string const & path);

//Reads all directories and returns a vector with fileNames that have one of the extensions
std::vector<std::string> StartReadingDirs();





#endif // !READDIR_H

