#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include "utility.h"

using namespace std;

class Logger {
public:
    Logger( string _fileName ) : fileName(_fileName) {}
    Logger& operator<<( const string& logMsg ) {
        Utility::addLineToFile( fileName, Utility::currentDateTime() + "  " + logMsg );
        return *this;
    }
    void line() {
        Utility::addLineToFile( fileName, "-------------------" );
    }
private:
    string fileName;
};

#endif /* _LOGGER_H_ */
