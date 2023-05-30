//
//  Logger.cpp
//  c_logHelp2
//
//  Created by Jamie  Hurd on 8/29/22.
//

#include <stdio.h>
#include "Logger.h"

Logger::Logger()
{

}

Logger::Logger(std::string *loggerString)
{
 
}

void Logger::setLogger(std::string *loggerString)
{
 logStruct.message = *loggerString;
}

std::string Logger::getStruct() const
{
 return *loggerString;
}
