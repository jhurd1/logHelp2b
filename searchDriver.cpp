#include <iostream>
#include <string>
#include "searchDirs.hpp"
#include <regex>
#include <array>

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
    int wordQuantity = 0;
    int j = 0;
    
    try {

       
        std::regex isMacPath("/.*/+");
        std::regex relativePath("^[^/].*");
        std::regex isWindowsPath("[a-zA-Z]:[\\//](?:[a-zA-Z0-9]+[\\/])*([a-zA-Z0-9]+\\.txt)");
        std::smatch match;

        std::cout << "Enter the file path to search ending with a '/': ";
        std::cin >> correspPath;
        std::cout << std::endl;
       
        if (std::regex_match(correspPath, isMacPath))
        {
            std::cout << "You truly seek the holy grail." << "\n" << "\n" << std::endl;
        }
        else if (std::regex_match(correspPath, isWindowsPath))
        {
            std::cout << "";
        }
        else
        {
            std::cout << "Path failed." << std::endl;
            main();
        }

        std::cout << "\n" << "Select the quantity of words--up to three:" << std::endl;
        std::cin >> wordQuantity;
        std::cout << std::endl;
        switch (wordQuantity)
        {
        case 1:
            j = 0;
            logic.prompt(correspPath);
            break;
        case 2:
            j = 1;
            logic.prompt(correspPath);
            break;
        case 3:
            j = 2;
            logic.prompt(correspPath);
            break;
        default:
            break;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "searchDriver failed." << std::endl;
    }

    return 0;
}
