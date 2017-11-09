#ifndef __DATE_H__
#define __DATE_H__

#include <string>

class Date {
public:
	Date(int _year, int _month, int _day) : year(_year), month(_month), day(_day) {}
	
private:
    int year;
    int month;
    int day;
};

Date str_to_date(std::string s);

#endif //__DATE_H__