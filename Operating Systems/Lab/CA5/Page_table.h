//
// Created by Sadegh on 1/8/18.
//

#ifndef CA5_PAGE_TABLE_H
#define CA5_PAGE_TABLE_H

#include <vector>
#include <utility>
#include <fstream>

using namespace std;

class Page_table {
public:
    Page_table(unsigned page_size);
    unsigned operator[](unsigned index);

    void add_index(unsigned index, unsigned address);
    void invalid_index(unsigned index);
private:

    struct Row {
        unsigned pys_address;
        bool is_valid;
    };

    unsigned page_size;
    vector<Row> table;
};

#endif //CA5_PAGE_TABLE_H
