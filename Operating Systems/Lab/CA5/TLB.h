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

private:

    unsigned find_free_row();

    struct Row {
        Row() {
            is_valid = false;
        }

        unsigned index;
        unsigned address;
        bool is_valid;
    };

    unsigned tlb_size;
    unsigned last_index = 0;
    vector<Row> table;
};


#endif //CA5_TLB_H
