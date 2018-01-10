#include <iostream>
#include <cassert>
#include <fstream>
#include <random>

#include "config.h"
#include "exception.h"
#include "Page_table.h"
#include "Memory.h"
#include "TLB.h"

using namespace std;
//TODO: TIME ro biyar ghablesh.
unsigned virt_to_phys(Page_table &pt, Memory &mem, TLB &tlb, unsigned index) {
    unsigned address;
    try {
        address = tlb[index];
        cout << "found in tlb" << endl;
    } catch (Not_found_in_tlb &e) {
        cout << "not found in tlb" << endl;
        try {
            address = pt[index];
            cout << "found in page_table" << endl;
        } catch (Page_fault &e) {

            cout << "page_fault occurs" << endl;
            try {
                cout << "try swap_in" << endl;
                address = mem.swap_in(index);
            } catch (Mem_full &e) {
                cout << "not enough space" << endl;
                unsigned swap_out = mem.swap_out();
                pt.invalid_index(swap_out);
                tlb.invalid_index(swap_out);
                address = mem.swap_in(index);
                cout << "swap in successful" << endl;
            }
            pt.add_index(index, address);
            cout << "page_table updated" << endl;

        }
        tlb.update(index, address);
        cout << "tlb updated" << endl;

    }
    return address;
}

string bin(unsigned i){
    return !i?"0":i==1?"1":bin(i/2)+(i%2?'1':'0');
}

int main(int argc, char *argv[]) {
    srand(0);

    if (argc != 4) {
        cout << "usage: ./a.out back_store.bin input.txt output.txt" << endl;
        exit(1);
    }
    string back_store_path = string(argv[1]);
    string input_path = string(argv[2]);
    string output_path = string(argv[3]);

    Page_table pt(PAGE_TABLE_SIZE);
    Memory mem(NUM_OF_FRAMES, back_store_path, SECOND_CHANCE);
    TLB tlb(TLB_SIZE);

    ifstream input(input_path, ios_base::in);
    assert(input.is_open());
    ofstream output(output_path, ios_base::out);
    assert(output.is_open());

    unsigned logical_address;
    while(input >> logical_address) {
        unsigned logical_page = (logical_address & PAGE_NUMBER_MASK) >> 8;
        unsigned offset = (logical_address & OFFSET_MASK);

        unsigned phys_page = virt_to_phys(pt, mem, tlb, logical_page);
        unsigned phys_address = phys_page * FRAME_SIZE + offset;

        unsigned data = mem[phys_address];

        cout << logical_page << ":" << offset << " -> " << phys_page << ":" << offset  << " (" << data << ")" << endl;
        output << data << endl;
    }

    unsigned TIME = tlb.get_TIME() + pt.get_TIME() + mem.get_TIME();
    cout << "TIME: " << TIME / 1000 << endl;

    return 0;
}