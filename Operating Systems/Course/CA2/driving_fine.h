#ifndef __DRIVING_FINE_H__
#define __DRIVING_FINE_H__

#include "date.h"

class Driving_fine {
public:
	Driving_fine(int _id, Date _date, long long _amount) : id(_id), date(_date), amount(_amount) {}

private:
	int id;
	Date date;
	long long amount;
};

#endif //__DRIVING_FINE_H__