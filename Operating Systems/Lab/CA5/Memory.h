//
// Created by Sadegh on 1/9/18.
//

#ifndef CA5_MEMORY_H
#define CA5_MEMORY_H

#include <vector>
#include <fstream>
#include <string>

#include "config.h"

using namespace std;

class Memory {
public:
    Memory(unsigned num_of_frames, string backing_store_path, int replacement_policy);

    unsigned operator[](unsigned index);

    unsigned int swap_in(unsigned index);
    unsigned swap_out();

    unsigned int get_TIME() const;

private:
    void swap_in_data(unsigned frame_index, unsigned data_index);
    void swap_out_data(unsigned frame_index);
    unsigned select_victim();
    unsigned fifo_replace();
    unsigned lru_replace();
    unsigned sc_replace();
    unsigned ran_replace();

    struct Frame {
        Frame() {
            this->is_valid = false;
            this->access_time = 0;
            this->reference_bit = 0;
            for (int i = 0; i < FRAME_SIZE; ++i) {
                strcpy(&data[i], "X");
            }
        }
        bool is_valid;
        unsigned real_index;
        char data[FRAME_SIZE];

        unsigned access_time;   // used for LRU replacement policies
        bool reference_bit;     // used for SECOND_CHANCE replacement policies
    };

    unsigned num_of_frames;
    fstream backing_store;
    vector<Frame> table;

    // used for replacement policies
    unsigned clk = 0;
    unsigned last_index = 0;
    int replacement_policy;                                                                                                             vector<char>d;

    unsigned TIME = 0;
};


#endif //CA5_MEMORY_H
