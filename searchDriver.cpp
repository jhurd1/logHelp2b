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
        std::cout << "\n" << std::endl;
        
        if (std::regex_match(correspPath, isMacPath))
        {
         logic.prompt(correspPath);
        }
        else
        {
         std::cout << "A bad path has resulted in an inoperable condition." << std::endl;
        }
        
    }
    catch (std::exception& e)
    {
        std::cout << "searchDriver failed." << std::endl;
    }
   
    return 0;
}
