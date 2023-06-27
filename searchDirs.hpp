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
   std::string stringInFile;
   int i;
   int j;
   const int words = 3;
   const int wordlength = 25;
   char array[3][25];
   int depth;
   bool sayWhen;
   
 public:
  
  SearchDirs();
  SearchDirs(std::string correspPath, SearchLogic s);
  SearchDirs(std::string correspPath, int depth, SearchLogic s);
  
  void setcorrespPath(std::string correspPath);
  void setstringInFile(std::string stringInFile);
  void setfilename(std::string filename);
  void setwords(const int *words);
  void setSayWhen(bool sayWhen);
  void setDepth(int depth);
  
  std::string getcorrespPath() const;
  std::string getstringtoFind() const;
  std::string getstringInFile() const;
  std::string getfilename() const;
  int getwords() const;
  bool getSayWhen() const;
  int getDepth() const;
  
  void dirContents(std::string correspPath, std::string outPath);
};

#endif /* searchDirs_hpp */
