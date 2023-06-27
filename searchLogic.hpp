#ifndef SEARCHLOGIC_H
#define SEARCHLOGIC_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "search.hpp"
#include <map>
#include <regex>

class SearchLogic
{
private:
    std::string *correspPath;
    std::string *replacement;
    std::string outPath;
    std::string line;
    Search search;
    //std::vector<std::string> *storeWords;
    int j = 0;
    std::regex isMacPath;
    
public:
    // Mutators
    void setcorrespPath(std::string *correspPath);
    void setoutpath(std::string outPath);
    void setIn(std::ifstream in);
    void setLine(std::string line);
    void setreplacement(std::string& replacement);
    void setJ(int j);
    void setStoreWords(std::vector<std::string> *storeWords);

    // Accessors
    std::string getcorrespPath() const;
    std::string getoutpath() const;
    std::string getLine() const;
    std::string getreplacement() const;
    int getJ() const;
    std::string getStrings() const;
    //std::vector<std::string> getStoredWords() const;

    // Constructors
    SearchLogic();
    SearchLogic(std::string *correspPath);
    SearchLogic(std::string correspPath,
        std::string& replacement);

    // Other Data Members
    int prompt(std::string &correspPath);
    //bool linehasthestring(std::string line, std::string stringToFind);
    void pushTheLines(std::string correspPath, std::string outPath);
    void testReadAndWrite(std::string correspPath, std::string outPath);
};
#endif
