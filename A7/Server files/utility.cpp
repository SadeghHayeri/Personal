#include "utility.h"
#include <fstream>
#include <exception>
#include <stdexcept>
#include <string>
#include <ctime>
#include <stdarg.h>

string Utility::replaceAll( const string str, const char from, const string to ) {
    string newStr;
    for (size_t i = 0; i < str.size(); i++) {
        if( str[i] != from )
            newStr += str[i];
        else
            newStr += to;
    }
    return newStr;
}

void Utility::clear() {
    #ifdef WINDOWS
    std::system("cls");
    #else
        // Assume POSIX
        std::system ("tput reset");
    #endif
}

void Utility::addLineToFile( string fileAddress, string line ) {

    // open file
    ofstream file;
    file.open( fileAddress.c_str(), ios::app );
    if( !file )
        throw std::invalid_argument( "can't open " + fileAddress );

    // add line
    file << line << endl;

}

void Utility::makeFile( string fileAddress ) {

    // open file
    ofstream file;
    file.open( fileAddress.c_str(), ios::app );
    if( !file )
        throw std::invalid_argument( "can't open " + fileAddress );

}

void Utility::makeFolder( string address ) {
    system( ("mkdir " + address + " -p").c_str() );
}

size_t Utility::hash( string text ) {
    return ::hash<string>{}(text);
}

bool Utility::fileExist( string fileAddress ) {
    ifstream f(fileAddress.c_str());
    return f.good();
}

string Utility::currentDateTime() {
    time_t now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

string Utility::to_string( int num ) {
    return ::to_string( num );
}

string Utility::getLastLine( string fileName ) {

    // open file
    ifstream file;
    file.open( fileName.c_str() );
    if( !file )
        throw std::invalid_argument( "can't open " + fileName );

    // WR: edit this line, for long text is too slow! (use seekg)
    string line;
    while( getline(file, line) ){
    }

    return line;

}

int Utility::stoi( string num ) {
    return ::stoi( num );
}
