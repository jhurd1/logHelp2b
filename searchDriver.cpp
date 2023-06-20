#include <iostream>
#include <string>
#include "searchDirs.hpp"
#include <regex>
#include <array>
#include <streambuf>

/* ****************************************
* SEARCHDRIVER
* The "main()" function that
* presses my objects into service.
*******************************************/

int main()
{
    SearchLogic logic;
    SearchDirs searchDirs;
    std::string word;
    std::string correspPath;
    
    try {
        std::regex isMacPath("/.*/+");
        std::regex relativePath("^[^/].*");
        std::regex isWindowsPath("[a-zA-Z]:[\\//](?:[a-zA-Z0-9]+[\\/])*([a-zA-Z0-9]+\\.txt)");
        std::smatch match;

        std::cout << "Enter the file path to search ending with a '/': ";
        std::cin >> correspPath;
        std::cout << std::endl;
        std::cout << std::endl;
  
        logic.prompt(correspPath);
    }
    catch (std::exception& e)
    {
        std::cout << "searchDriver failed." << std::endl;
    }
    
    return 0;
}
