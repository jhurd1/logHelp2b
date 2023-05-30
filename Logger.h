//
//  Logger.h
//  c_logHelp2
//
//  Created by Jamie  Hurd on 8/29/22.
//

#ifndef Logger_h
#define Logger_h
#include <string>

class Logger
{
// A custom data structure for the Logger class.
 struct
 {
  std::string message;
 } logStruct;
 
 // Private data members for the Logger.
 private:
  std::string *loggerString;
  
  // Constructors, accessors, mutators, and other data members.
 public:
   Logger();
   Logger(std::string *loggerString);
   
   void setLogger(std::string *loggerString);
   
   std::string getStruct() const;
};

#endif /* Logger_h */
