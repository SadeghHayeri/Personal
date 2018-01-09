//
// Created by Sadegh on 1/9/18.
//

#include "Memory.h"
#include <cassert>
#include <random>
#include "exception.h"


Memory::Memory(unsigned num_of_frames, string backing_store_path) {
    this->num_of_frames = num_of_frames;
    this->table = vector<Frame>(num_of_frames, Frame());
    this->backing_store.open(backing_store_path, ios_base::in | ios::binary);

    assert(this->backing_store.is_open());
}

string Memory::operator[](unsigned index) {
    assert(index < num_of_frames);
    assert(table[index].is_valid);

    table[index].access_time = ++clk;
    table[index].reference_bit = true;
    return string(table[index].data);
}

unsigned int Memory::swap_in(unsigned int index) {
    for (int i = 0; i < num_of_frames; ++i) {
        if(!table[i].is_valid) {
            swap_data_in_to(index, i);
            table[i].is_valid = true;
            return i;
        }
    }

    throw Mem_full("MEMORY IS FULL");
}

unsigned Memory::select_victim() {
#ifdef FIFO
    return fifo_replace();
#elif LRU
    return lru_replace();
#elif SECOND_CHANCE
    return sc_replace();
#elif RANDOM_REPLACEMENT
    return ran_replace();
#endif
}

unsigned Memory::swap_out() {
    unsigned victim = select_victim();
    table[victim].is_valid = false;
    return victim;
}

void Memory::swap_data_in_to(unsigned frame_index, unsigned data_index) {
    backing_store.seekg(ios_base::beg);
    backing_store.seekg(data_index * FRAME_SIZE * DATA_SIZE);

    backing_store.read(table[frame_index].data, FRAME_SIZE);
}

unsigned Memory::fifo_replace() {
    return ++last_index;
}

unsigned Memory::lru_replace() {
    unsigned min_index = 0;

    for(unsigned i = 0; i < num_of_frames; ++i)
        if(table[i].access_time < table[min_index].access_time)
            min_index = i;

    return min_index;
}

unsigned Memory::sc_replace() {
    while(true) {

        unsigned index = ++last_index % num_of_frames;
        if(table[index].reference_bit)
            table[index].reference_bit = false;
        else
            return index;

    }
}

unsigned Memory::ran_replace() {
    return rand() % num_of_frames;
}
