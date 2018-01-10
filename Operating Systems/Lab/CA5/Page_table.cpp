//
// Created by Sadegh on 1/8/18.
//
#include "Page_table.h"
#include <cassert>
#include "exception.h"
#include "config.h"

Page_table::Page_table(unsigned page_size) {
    this->page_size = page_size;
    this->table = vector<Entry>(page_size, {0, false});
}

unsigned Page_table::operator[](unsigned index) {
    assert(index <= page_size);
    TIME += MEM_DELAY;

    if(table[index].is_valid)
        return table[index].pys_address;

    throw Page_fault("PAGE_TABLE");
}

void Page_table::add_index(unsigned index, unsigned pys_address) {
    assert(index <= page_size);
    TIME += MEM_DELAY;

    table[index].is_valid = true;
    table[index].pys_address = pys_address;
}

void Page_table::invalid_index(unsigned index) {
    assert(index <= page_size);
    TIME += MEM_DELAY;

    table[index].is_valid = false;
}

unsigned int Page_table::get_TIME() const {
    return TIME;
}
