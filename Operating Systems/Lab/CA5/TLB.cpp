//
// Created by Sadegh on 1/8/18.
//

#include "TLB.h"
#include "exception.h"
#include <cassert>
#include "config.h"

TLB::TLB(unsigned tlb_size) {
    this->tlb_size = tlb_size;
    this->table = vector<Entry>(tlb_size, Entry());
}

unsigned TLB::operator[](unsigned index) {
    TIME += TLB_DELAY;
    for(Entry &entry : table)
        if(entry.is_valid && entry.index == index)
            return entry.address;

    throw Not_found_in_tlb("TLB");
}

unsigned TLB::find_free_entry() {
    for (unsigned i = 0; i < tlb_size; ++i)
        if(!table[i].is_valid)
            return i;

    return (last_index++) % tlb_size;
}

void TLB::update(unsigned index, unsigned address) {
    TIME += TLB_DELAY;
    unsigned free_entry = find_free_entry();
    table[free_entry].is_valid = true;
    table[free_entry].index = index;
    table[free_entry].address = address;
}

void TLB::invalid_index(unsigned index) {
    TIME += TLB_DELAY;
    for(Entry &entry : table)
        if(entry.index == index)
            entry.is_valid = false;
}

unsigned int TLB::get_TIME() const {
    return TIME;
}
