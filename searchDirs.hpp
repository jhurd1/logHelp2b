//
//  searchDirs.hpp
//  c_logHelp2
//
//  Created by Jamie  Hurd on 6/30/22.
//

#ifndef searchDirs_hpp
#define searchDirs_hpp

#include <stdio.h>
#include <dirent.h>
#include <string>
#include "searchLogic.hpp"
#include <map>

class SearchDirs
{
 SearchLogic s;
 private:
   std::string correspPath;
   std::string *stringToFind;
   std::string stringInFile;
   int i;
   int j;
   const int words = 3;
   const int wordlength = 25;
   char array[3][25];
   
 public:
  
  SearchDirs();
  SearchDirs(std::string correspPath, SearchLogic s);
  SearchDirs(std::string correspPath, std::string *stringToFind, SearchLogic s);
  
  void setcorrespPath(std::string correspPath);
  void setstringtoFind(std::string *stringToFind);
  void setstringInFile(std::string stringInFile);
  void setfilename(std::string filename);
  void setwords(const int *words);
  
  std::string getcorrespPath() const;
  std::string getstringtoFind() const;
  std::string getstringInFile() const;
  std::string getfilename() const;
  int getwords() const;
  
  void dirContents(std::string correspPath, std::string *stringToFind);
};

#endif /* searchDirs_hpp */
