//
// Created by Sadegh on 1/9/18.
//
#ifndef CA5_EXCEPTION_H
#define CA5_EXCEPTION_H

#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

class Not_found_in_tlb : public runtime_error {
public:
    Not_found_in_tlb(const string &what) : runtime_error(what) {}
};

class Page_fault : public runtime_error {
public:
    Page_fault(const string &what) : runtime_error(what) {}
};

class Mem_full : public runtime_error {
public:
    Mem_full(const string &what) : runtime_error(what) {}
};


#endif //CA5_EXCEPTION_H
