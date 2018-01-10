//
// Created by Sadegh on 1/9/18.
//

#include "Memory.h"
#include <cassert>
#include <random>
#include "exception.h"
#include <exception>


Memory::Memory(unsigned num_of_frames, string backing_store_path, int replacement_policy) {
    this->num_of_frames = num_of_frames;
    this->table = vector<Frame>(num_of_frames, Frame());
    this->backing_store.open(backing_store_path, ios_base::in | ios_base::out | ios::binary);
    this->replacement_policy = replacement_policy;

    assert(this->backing_store.is_open());
    assert(replacement_policy == FIFO ||
            replacement_policy == LRU ||
            replacement_policy == SECOND_CHANCE ||
            replacement_policy == RANDOM_REPLACEMENT);
}

unsigned Memory::operator[](unsigned index) {
    unsigned frame_index = index / FRAME_SIZE;
    unsigned offset_index = index % FRAME_SIZE;

    assert(index < num_of_frames * FRAME_SIZE);
    assert(table[frame_index].is_valid);
    TIME += MEM_DELAY;

    table[frame_index].access_time = ++clk;
    table[frame_index].reference_bit = true;
    return (unsigned)(table[frame_index].data[offset_index]);
}

unsigned Memory::select_victim() {
    switch(replacement_policy) {
        case FIFO:
            return fifo_replace();
            break;
        case LRU:
            return lru_replace();
            break;
        case SECOND_CHANCE:
            return sc_replace();
            break;
        case RANDOM_REPLACEMENT:
            return ran_replace();
            break;
        default:
            throw bad_exception();
    }
}

unsigned int Memory::swap_in(unsigned int index) {
    for (unsigned i = 0; i < num_of_frames; ++i) {
        if(!table[i].is_valid) {
            swap_in_data(index, i);
            table[i].is_valid = true;
            return i;
        }
    }

    throw Mem_full("MEMORY IS FULL");
}

unsigned Memory::swap_out() {
    unsigned victim = select_victim();
    swap_out_data(victim);
    table[victim].is_valid = false;
    return victim;
}

void Memory::swap_in_data(unsigned frame_index, unsigned data_index) {
    TIME += MEM_DELAY + DISK_DELAY;
    backing_store.seekg(ios_base::beg);
    backing_store.seekg(data_index * FRAME_SIZE * DATA_SIZE);

    backing_store.read(table[frame_index].data, FRAME_SIZE);
    table[frame_index].real_index = data_index;
}

void Memory::swap_out_data(unsigned frame_index) {
    TIME += MEM_DELAY + DISK_DELAY;
    backing_store.seekg(ios_base::beg);
    backing_store.seekg(table[frame_index].real_index * FRAME_SIZE * DATA_SIZE);

    //backing_store.write(table[frame_index].data, FRAME_SIZE); // no need
}

unsigned Memory::fifo_replace() {
    TIME += MEM_DELAY;
    return ++last_index;
}

unsigned Memory::lru_replace() {
    unsigned min_index = 0;

    for(unsigned i = 0; i < num_of_frames; ++i) {
        TIME += MEM_DELAY;
        if (table[i].access_time < table[min_index].access_time)
            min_index = i;
    }

    return min_index;
}

unsigned Memory::sc_replace() {
    while(true) {
        TIME += MEM_DELAY;  // read reference_bit
        TIME += MEM_DELAY;  // change reference_bit

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

unsigned int Memory::get_TIME() const {
    return TIME;
}
