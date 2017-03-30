#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

class Utility {
public:
    static string replaceAll( const string str, const char from, const string to );
    static void clear();
    static void addLineToFile( string fileAddress, string line );
    static bool fileExist( string fileAddress );
    static void makeFile( string fileAddress );
    static void makeFolder( string address );
    static size_t hash( string text );
    static string currentDateTime();
    static string to_string( int num );
    static string getLastLine( string fileName );
    static int stoi( string num );
};

#endif /* _UTILITY_H_ */
