//
//  searchDirs.cpp
//  c_logHelp2
//
//  Created by Jamie  Hurd on 6/30/22.
//

#include "searchDirs.hpp"
#include "searchLogic.hpp"
#include <filesystem>
#include <array>

/* ***************************
* CONSTRUCTORS
*******************************/

/***************
* Default.
***************/
SearchDirs::SearchDirs()
{
 
}

/**************************
* Non-default, one.
* Note: The colon
* following the signature
* prevents the invocation
* of the default constructor.
* It intializes members before
* the body executes.
***************************/
 SearchDirs::SearchDirs(std::string correspPath, SearchLogic s) : s(s)
 {
  setcorrespPath(correspPath);
 }
 
 /*******************
* Non-default, two.
*********************/
 SearchDirs::SearchDirs(std::string correspPath, int depth,
  SearchLogic s) : s(s)
 {
  setcorrespPath(correspPath);
  //setstringtoFind(stringToFind);
  setDepth(depth);
 }
 
/* *******************************
* MUTATORS
*********************************/

/*******************
* setcorrespPath
********************/
 void SearchDirs::setcorrespPath(std::string correspPath)
 {
  this->correspPath = s.getcorrespPath();
 }
 
 /*******************
* setSayWhen
********************/
  void SearchDirs::setSayWhen(bool sayWhen)
  {
   this->sayWhen = sayWhen;
  }
 
 /*******************
* setstringtofind
*********************/
 /*void SearchDirs::setstringtoFind(std::string *stringToFind)
 {
  std::string t("");
  stringToFind = &t;
  t = s.getstringToFind();
  this->stringToFind = &t;
 }*/
 
 /******************************
 * setDepth()
 *******************************/
 void SearchDirs::setDepth(int depth)
 {
  this->depth = depth;
 }
 
 
/* *******************************
* ACCESSORS
*********************************/

/*****************
* getcorresppath
******************/
 std::string SearchDirs::getcorrespPath() const
 {
  return s.getcorrespPath();
 }
 
 /********************
* getstringtofind
*********************/
 /*std::string SearchDirs::getstringtoFind() const
 {
  return *stringToFind;
 }*/
 
 /********************
* getstringinfile
**********************/
 std::string SearchDirs::getstringInFile() const
 {
  return stringInFile;
 }
 
/********************
* getSayWhen()
**********************/
bool SearchDirs::getSayWhen() const
{
 return sayWhen;
}
 
 /*******************************
 * getDepth()
 *******************************/
 int SearchDirs::getDepth() const
 {
  return depth;
 }
 
 
 /* *******************************
* OTHER DATA MEMBERS
**********************************/

 /* **********************************
* DIRCONTENTS
* Take the search path
* Drill into subdirectories
* Call partner function, pushTheLines()
***************************************/
void SearchDirs::dirContents(std::string correspPath, std::string outPath)
{
 for (const auto &initEntry : std::filesystem::recursive_directory_iterator(correspPath))
 {
  depth++;
  setDepth(depth);
 }
 
 std::cout << "Depth: " << " " << depth << std::endl;
 
 try
 {
 // Use a marker to the end of the loop to signal pushTheLines when to close the in stream.
 for(const auto &entry : std::filesystem::recursive_directory_iterator(correspPath))
  {
   // Gives the custom depth at the end of the run.
   // Report the depth.
   // Reveal the depth.
   // Hold the depth in memory.
   // If, from SearchLogic, a count exceeds depth from this class, close the stream.
    if (entry.is_regular_file())
    {
     {
      SearchLogic sl;
      correspPath = entry.path();
      std::filesystem::path path(correspPath);
      std::string file = path.filename().string();
     if ((file != ".DS_Store") && (file.substr(file.find_last_of(".") + 1) != "docx"))
     {
      sl.pushTheLines(correspPath, outPath);
     }
    }
    }
   }

 } catch (std::exception &e)
 {
  std::cout << "Recursive iteration failed from dirContents() in searchDirs" << std::endl;
 }
}
    
