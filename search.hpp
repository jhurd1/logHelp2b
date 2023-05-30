#ifndef SEARCH_H
#define SEARCH_H
#include <string>

class Search
{
    private:
    
        std::string *fpath;
        std::string searchStrings;

    public:
    
        void setPath(std::string *fpath);
        void setStrings(std::string searchStrings);

        std::string getPath() const;
        std::string getStrings() const;
        
        Search();

        Search(std::string *fpath);

        Search(std::string *fpath, std::string searchStrings);

};


#endif
