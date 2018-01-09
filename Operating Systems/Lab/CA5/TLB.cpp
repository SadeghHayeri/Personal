//
// Created by Sadegh on 1/8/18.
//

#include "TLB.h"
#include "exception.h"
#include <cassert>

TLB::TLB(unsigned tlb_size) {
    this->tlb_size = tlb_size;
    this->table = vector<Row>(tlb_size, Row());
}

unsigned TLB::operator[](unsigned index) {
    for(Row &row : table)
        if(row.is_valid && row.index == index)
            return row.address;

    throw Not_found_in_tlb("TLB");
}

unsigned TLB::find_free_row() {
    for (unsigned i = 0; i < tlb_size; ++i)
        if(!table[i].is_valid)
            return i;

    return (last_index++) % tlb_size;
}

void TLB::update(unsigned index, unsigned address) {
    unsigned free_row = find_free_row();
    table[free_row].is_valid = true;
    table[free_row].index = index;
    table[free_row].address = address;
}

void TLB::invalid_index(unsigned index) {
    for(Row &row : table)
        if(row.index == index)
            row.is_valid = false;
}
