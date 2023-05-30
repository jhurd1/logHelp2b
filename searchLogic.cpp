#include "searchLogic.hpp"
#include "search.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <cctype>
#include <array>
#include "searchDirs.hpp"
#include "Logger.h"

/* ***************************
* CONSTRUCTORS
*******************************/


/***************
* Default.
***************/
SearchLogic::SearchLogic()
{
  
}

/********************
* Non-default
*********************/
SearchLogic::SearchLogic(std::string *correspPath)
{
    setcorrespPath(correspPath);
}

/*****************
* Non-default
******************/
SearchLogic::SearchLogic(std::string correspPath, std::string stringToFind,
    std::string& replacement)
{
    setcorrespPath(&correspPath);
    setstringToFind(stringToFind);
    setreplacement(replacement);
}

/* *******************************
* MUTATORS
*********************************/

/*****************
* setcorrespPath
******************/
void SearchLogic::setcorrespPath(std::string *correspPath)
{
  *correspPath = search.getPath();
  //this->correspPath = search.getPath();
}

/*****************
* setstringtofind
******************/
void SearchLogic::setstringToFind(std::string stringToFind)
{
    this->stringToFind = stringToFind;
}

/*****************
* setline
******************/
void SearchLogic::setLine(std::string line)
{
    this->line = line;
}

void SearchLogic::setoutpath(std::string outPath)
{
    this->outPath = outPath;
}


/* *****************
* setreplacement
********************/
void SearchLogic::setreplacement(std::string& replacement)
{
    replacement = " REDACTED ";
    this->replacement = &replacement;
}

/**************************
* setJ
**************************/
void SearchLogic::setJ(int j)
{
    this->j = j;
}

/**************************
* setStringsToFind
* To get this to work as
* expected, check on
* correct assignment
* during debug.
**************************/
void SearchLogic::setStringsToFind(std::string stringsToFind)
{
 int i = 0;
 this->stringsToFind[i] = &stringToFind;
}

/* *******************************
* ACCESSORS
**********************************/

/*****************
* getcorresppath
******************/
std::string SearchLogic::getcorrespPath() const
{
    return *correspPath;
}

/*****************
* getstringtofind
******************/
std::string SearchLogic::getstringToFind() const
{
    return stringToFind;
}

std::string SearchLogic::getoutpath() const
{
    return outPath;
}

/*****************
* getline
******************/
std::string SearchLogic::getLine() const
{
    return line;
}

/*****************
* getreplacement
******************/
std::string SearchLogic::getreplacement() const
{
    return *replacement;
}

/*********************
* getJ
********************/
int SearchLogic::getJ() const
{
    return j;
}

/**************************
* getStrings()
**************************/
std::string SearchLogic::getStrings() const
{
 int i = 0;
 return *stringsToFind[i];
}

/* **********************************
* LINEHASTHESTRING
* Return whether the search word
* exists in a line.
***************************************/
bool SearchLogic::linehasthestring(const std::string& line, std::string stringToFind)
{

    return (line.find(stringToFind) != std::string::npos);
}

/* *******************************
* OTHER DATA MEMBERS
* Prompt for user input.
**********************************/
int SearchLogic::prompt(std::string &correspPath)
{
    SearchDirs searchDirs;
    std::regex isnumber("^-?\\d+");
    try
    {
     std::cout << "Output file path: " << "\n" << std::endl;
     std::cin >> outPath;
     std::cout << std::endl;
     if(!outPath.empty())
      {
       std::cout << "Search word: " << "\n" << std::endl;
       std::cin >> stringToFind;
       for (int i = 0; i <= j; i++)
       {
        stringsToFind[i] = &stringToFind;
        if (std::regex_match(stringToFind, isnumber))
        {
           std::cout << "Inappropriate data type for input." << std::endl;
           return 1;
        }
         else
        {
           searchDirs.dirContents(correspPath, &stringToFind);
        }
       }
      } else
      {
       Logger l;
       std::string *mes = nullptr;
       std::string test = "ERROR: The program won't use this type of file.";
       mes = &test;
       l.setLogger(mes);
       std::cout << mes << std::endl;
       FILE *pFile;
       pFile = fopen("/users/jamiehurd/desktop/temp/logfile.log/", "w");
       if(pFile != NULL)
       {
        char const *temp = mes->c_str();
        fputs(temp, pFile);
        fclose(pFile);
       }
      }
    } catch (std::exception &e)
    {
     std::cout << "" << std::endl;
    }
    return j; //bad access
}

/* **********************************
* SEARCHLOGIC
* Opens the read stream
* Discern a line with a match
* Overwrite as needed
* Output to a new file.
***************************************/
void SearchLogic::pushTheLines(std::string correspPath,
    std::string stringToFind)
{
    std::fstream in;
    std::string line;
    std::string replacement = " REDACTED ";

    try
    {
        in.open(correspPath, std::ios::in);

        while (in)
        {
            std::getline(in, line);
            //Test line by outputting its value to console.
            std::cout << "Test cout itself." << std::endl;
            std::cout << "Line's value is " + line << "\n";
            if (linehasthestring(line, stringToFind))
            {
                std::istringstream ss(line);
                std::string word;
                while (ss >> word)
                {
                    if (word.length() && word.back() == '.')
                    {
                        word.pop_back();
                    }
                    std::regex r("\\b(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\b");
                    std::regex m("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
                    std::smatch match;
                    auto iter = line.find(word);
                    while (iter != std::string::npos)
                    {
                        if (std::regex_match(word, r) || (std::regex_match(word, m)))
                        {
                            size_t s = line.find(word);
                            line.replace(s, word.length() + 1, replacement);
                            iter = line.find(word, iter);
                            std::ofstream out(outPath, std::fstream::app);
                            out << line << std::endl;
                            out.close();
                        }
                        else
                        {
                            std::ofstream out(outPath, std::fstream::app);
                            out << line << std::endl;
                        }
                    }
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout << "Error opening file." << std::endl;
    }
    in.close();
    
}
