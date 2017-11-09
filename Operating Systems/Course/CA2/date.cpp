#include "date.h"

using namespace std;

Date str_to_date(string s) {
    int slash_pos = s.find('-');
    int y = atoi(s.substr(0, slash_pos).c_str());
    s = s.substr(slash_pos + 1);
    slash_pos = s.find('-');
    int m = atoi(s.substr(0, slash_pos).c_str());
    int d = atoi(s.substr(slash_pos + 1).c_str());

    return Date(d, m, y);
}
