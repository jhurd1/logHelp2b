#include <iostream>
#include <iomanip>
#include <string>
#include "search.hpp"

/* ********************
* CONSTRUCTORS
***********************/

/***************
* Default.
***************/
Search::Search()
{
    
}

/********************
* Non-default, one.
*********************/
Search::Search(std::string *fpath)
{
    setPath(fpath);
}

/*****************
* Non-default, two.
******************/
Search::Search(std::string *fpath, std::string searchStrings)
{
    setPath(fpath);
    setStrings(searchStrings);
}

/* *******************************
* MUTATORS
*********************************/

/*****************
* setstrings
******************/
void Search::setStrings(std::string searchStrings)
{
    this->searchStrings = searchStrings;
}

/*******************
* setpath
********************/
void Search::setPath(std::string *fpath)
{
    this->fpath = fpath;
}

/* *******************************
* ACCESSORS
**********************************/

/********************
* getstrings
*********************/
std::string Search::getStrings() const
{
    return searchStrings;
}

/*******************
* getpath
********************/
std::string Search::getPath() const
{
    return *fpath; // dirContents appears to stop abruptly here.
}



