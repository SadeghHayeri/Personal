#ifndef __DRIVING_FINE_H__
#define __DRIVING_FINE_H__

class DrivingFine {
public:
	DrivingFine(int _id, Date _date, long long _amount) : id(_id), date(_date), amount(_amount);

private:
	int id;
	Date date;
	long long amount;
};

#endif //__DRIVING_FINE_H__