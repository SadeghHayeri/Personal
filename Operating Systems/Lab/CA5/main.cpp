#include <iostream>
#include <random>
#include "TLB.h"
#include "Page_table.h"
#include "Memory.h"
#include "TLB.h"
#include "config.h"

#include "exception.h"

using namespace std;

Page_table pt(PAGE_TABLE_SIZE);
Memory mem(NUM_OF_FRAMES, BACKING_STORE_PATH);
TLB tlb(TLB_SIZE);

unsigned virt_to_phys(unsigned index) {
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
    mem[address];
    return address;
}

int main() {

    srand(0);
    cout << virt_to_phys(0) << endl;
    cout << virt_to_phys(100) << endl;
    return 0;
}