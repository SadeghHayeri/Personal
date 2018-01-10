//
// Created by Sadegh on 1/8/18.
//

#ifndef CA5_TLB_H
#define CA5_TLB_H

#include <vector>

using namespace std;

class TLB {
public:
    TLB(unsigned tlb_size);
    unsigned operator[](unsigned index);

    void update(unsigned index, unsigned address);
    void invalid_index(unsigned index);
    unsigned int get_TIME() const;

private:

    unsigned find_free_entry();

    struct Entry {
        Entry() {
            is_valid = false;
        }

        unsigned index;
        unsigned address;
        bool is_valid;
    };

    unsigned tlb_size;
    unsigned last_index = 0;
    vector<Entry> table;

    unsigned TIME = 0;
};


#endif //CA5_TLB_H
