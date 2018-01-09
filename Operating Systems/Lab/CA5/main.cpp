#include <iostream>
#include <random>
#include "TLB.h"
#include "Page_table.h"
#include "Memory.h"
#include "TLB.h"
#include "config.h"
#include <fstream>

#include "exception.h"
#include <cassert>

unsigned TIME = 0;

using namespace std;

unsigned virt_to_phys(Page_table &pt, Memory &mem, TLB &tlb, unsigned index) {
    unsigned address;
    try {
        address = tlb[index];                               TIME += 5;
        cout << "found in tlb" << endl;
    } catch (Not_found_in_tlb &e) {
        cout << "not found in tlb" << endl;
        try {
            address = pt[index];                            TIME += 1000;
            cout << "found in page_table" << endl;
        } catch (Page_fault &e) {

            cout << "page_fault occurs" << endl;
            try {
                cout << "try swap_in" << endl;
                address = mem.swap_in(index);               TIME += 1000;   TIME += 2500000;
            } catch (Mem_full &e) {
                cout << "not enough space" << endl;
                unsigned swap_out = mem.swap_out();         TIME += 1000;   TIME += 2500000;
                pt.invalid_index(swap_out);                 TIME += 1000;
                tlb.invalid_index(swap_out);                TIME += 5;
                address = mem.swap_in(index);               TIME += 1000;   TIME += 2500000;
                cout << "swap in successful" << endl;
            }
            pt.add_index(index, address);                   TIME += 1000;
            cout << "page_table updated" << endl;

        }
        tlb.update(index, address);                         TIME += 5;
        cout << "tlb updated" << endl;

    }
    mem[address];
    return address;
}

string bin(unsigned i){
    return !i?"0":i==1?"1":bin(i/2)+(i%2?'1':'0');
}

int main(int argc, char *argv[]) {

    if (argc != 4) {
        cout << "usage: ./a.out back_store.bin input.txt output.txt" << endl;
        exit(1);
    }
    string back_store_path = string(argv[1]);
    string input_path = string(argv[2]);
    string output_path = string(argv[3]);

    Page_table pt(PAGE_TABLE_SIZE);
    Memory mem(NUM_OF_FRAMES, back_store_path, FIFO);
    TLB tlb(TLB_SIZE);

    fstream input("input.txt");
    assert(input.is_open());
    fstream output("input.txt", ios_base::out);
    assert(output.is_open());

    unsigned logical_address;
    while(input >> logical_address) {
        cout << bin(logical_address) << endl;
        unsigned phys_address = virt_to_phys(pt, mem, tlb, (logical_address & PAGE_NUMBER_MASK) >> 8);
        cout << bin(phys_address) << endl;
        phys_address *= FRAME_SIZE;
        phys_address += logical_address & OFFSET_MASK;

        output << logical_address << endl;
    }
    cout << TIME / 1000 << endl;

    return 0;
}