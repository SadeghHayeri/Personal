#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <cmath>
#define PI 3.14159265
using namespace std;


struct coordinate {
	float x, y;
};

struct speedElements {
    float x, y;
};

string replaceAll( string &str, char from, char to );
float getDistance( coordinate a, coordinate b );

coordinate operator+( coordinate a, coordinate b );
coordinate operator-( coordinate a, coordinate b );

#endif /* _UTILITY_H_ */
