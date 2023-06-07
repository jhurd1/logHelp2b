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


/****************************
* DATA MEMBERS
*****************************/
std::regex isMacPathFile("^/([A-Za-z0-9]+(/[A-Za-z0-9]+)+)\\.[A-Za-z0-9]+$");


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
bool SearchLogic::linehasthestring(std::string line, std::string stringToFind)
{
 std::cout << "linehasthestring sees the following 'line' value: \n" + line << std::endl;
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
  if(/*!outPath.empty() && */std::regex_match(outPath, isMacPathFile))
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
     searchDirs.dirContents(correspPath, &stringToFind, outPath);
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
 return j;
}

/* **********************************
 * SEARCHLOGIC
 * Opens the read stream
 * Discern a line with a match
 * Overwrite as needed
 * Output to a new file.
 ***************************************/
void SearchLogic::pushTheLines(std::string correspPath,
                               std::string stringToFind,
                               std::string outPath)
{
 std::ifstream in;
 std::string line;
 std::string replacement = " REDACTED ";
 std::stringstream ss;
 std::regex r("\\b(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\b");
 std::regex m("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
 std::string word;
 auto iter = line.find(word);
 std::smatch match;
 
 try
 {
  std::cout << "pushTheLines() try block entry\n" << std::endl;
  std::cout << "The path: " + correspPath << "\n" << std::endl;
  in.open(correspPath, std::ios::in);
  
  while (std::getline(in, line))
  {
   std::cout << "The line's value is\n" + line << "\n";
   std::cout << std::endl;
   if (linehasthestring(line, stringToFind))
   {
    std::cout << std::endl;
    std::cout << "I passed linehasthestring() \n" + line << "and " + stringToFind << std::endl;
    if (word.length() && word.back() == '.')
    {
     word.pop_back(); // Does not retain its new comma-less value afterward.
     std::cout << "Word's new value after 'popping off the dot or period: '" << word << std::endl;
    }
    else
    {
     while (in >> word)
     {
      std::cout << "I entered the regex loop.\n" << std::endl;
      std::cout << "Word's value comprises " << word << std::endl;
      std::cout << std::endl;
      if (std::regex_match(word, r) || (std::regex_match(word, m)))
      {
       std::cout << "I found a matching expression.\n" << std::endl;
       std::cout << std::endl;
       size_t s = line.find(word);
       std::cout << "Can I see 'replacement's' value? " << replacement << std::endl;
       line.replace(s, word.length() + 1, replacement);
       iter = line.find(word, iter);
       std::ofstream out(outPath, std::fstream::app);
       std::cout << "The output file's location is " << outPath << std::endl;
       std::cout << std::endl;
       out << line << std::endl;
       out.close();
       //break;
      }
      else
      {
       std::cout << "I didn't find a matching expression\n" << std::endl;
       std::ofstream out(outPath, std::fstream::app);
       out << line << std::endl;
       //break;
      }
     }
    }
   }
  }
 }
 catch (std::exception& e)
 {
  std::cout << "I threw an exception from pushTheLines()." << std::endl;
 }
 in.close();
 
}
