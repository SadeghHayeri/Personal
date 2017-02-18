#include "utility.h"

string replaceAll( string &str, char from, char to ) {
    string newStr;
    for (int i = 0; i < str.size(); i++) {
        if( str[i] != from )
            newStr += str[i];
        else
            newStr += to;
    }
    return newStr;
}

float getDistance( coordinate a, coordinate b ) {
    return sqrt( pow(a.x - b.x, 2) + pow(a.y - b.y, 2) );
}

coordinate operator+( coordinate a, coordinate b ) {
    coordinate result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

coordinate operator-( coordinate a, coordinate b ) {
    coordinate result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}
