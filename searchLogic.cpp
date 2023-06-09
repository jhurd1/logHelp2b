#include "searchLogic.hpp"
#include "search.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <cctype>
#include <array>
#include <string>
#include <vector>
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
SearchLogic::SearchLogic(std::string correspPath,
                         std::string& replacement)
{
 setcorrespPath(&correspPath);
 //setStoreWords(storeWords);
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

/*void SearchLogic::setStoreWords(std::vector<std::string> *storeWords)
{
 this->storeWords = storeWords;
}*/

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

 /*std::vector<std::string> SearchLogic::getStoredWords() const
 {
  return *storeWords;
 }*/

/* *******************************
 * OTHER DATA MEMBERS
 * Prompt for user input.
 **********************************/
int SearchLogic::prompt(std::string &correspPath)
{
 std::regex isnumber("^-?\\d+");
 
 try
 {
  std::cout << "Output file path: " << "\n" << std::endl;
  std::cin >> outPath;
  
  if(!outPath.empty() && std::regex_match(outPath, isMacPathFile))
  {
     pushTheLines(correspPath, outPath);
     //testReadAndWrite(correspPath, outPath);
     
  }
 } catch (std::exception &e)
 {
  std::cout << "Prompt() reached an exception." << std::endl;
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
void SearchLogic::pushTheLines(std::string correspPath, std::string outPath)
{
 std::string replacement = " REDACTED ";
 std::ofstream out(outPath);
 // IPv4 address.
 std::regex r("\\b(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\b");
 
 // MAC address.
 std::regex m("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
 
 std::string word;
 std::smatch match;
 
 int n = 0;
 std::vector<std::string> storeWords(n);
 
 try
 {
  for(const auto &entry : std::filesystem::recursive_directory_iterator(correspPath))
  {
   if (entry.is_regular_file())
   {
    {
     correspPath = entry.path();
     std::filesystem::path path(correspPath);
     std::string file = path.filename().string();
     if ((file != ".DS_Store") && (file.substr(file.find_last_of(".") + 1) != "docx"))
     {
      n++; //Proves necessary to coerce the vector into holding everything.
      std::ifstream in(correspPath);

      while (in >> word)
      {
       if (word.length() && word.back() == '.')
       {
        word.pop_back();
       }
       
       if ((std::regex_match(word, r) || (std::regex_match(word, m))))
       {
        word = replacement;
        
        storeWords.push_back(word);
       } else
       {
        
        storeWords.push_back(word);
       }
      }
      if (out.is_open())
      {
       
      }
       in.close();
     }
    }
   }
  }
  // Iterate over the vector and write.
  for (const std::string& words : storeWords) out << " " << words;
 }
 catch (std::exception& e)
 {
  std::cout << "pushTheLines() exception." << std::endl;
 }
 
 out.close();
}

/* **********************************
 * TEST WRITE
 ***************************************/

void SearchLogic::testReadAndWrite(std::string correspPath, std::string outPath)
{
     std::fstream in;
     std::string testWord, inFile;
     correspPath = "/Users/jamiehurd/Desktop/temp/test.log";
     
     in.open(correspPath);
     
     std::ofstream outty(outPath);
     
     while (in >> testWord)
     {
      std::cout << testWord << std::endl;

      outty << " " << testWord;
     }
     
     in.close();
     outty.close();
}
