#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <vector>
#include <pthread.h>
#include <mutex>
#include "semaphore.h"
#include "structs.h"

using namespace std;

class Node {
public:
    Node(int _id, int _input_size, double _input[], double* _output, Activation_function _af, Semaphore* _a_sem, Semaphore* _b_sem, Semaphore* _c_sem, bool* _initial_complete, vector<bool>* _node_compute, mutex* _node_compute_mtx);

    void set_weight(vector<double> _weight);
    void set_bias(double _bias);

    void serial_compute();

private:
    int id;
    static void* compute_core(void* arg);
    bool is_ready();
    void check_all_computed();

    bool* initial_complete;

    Activation_function af;

    int input_size;
    double* input;
    double* output;

    vector<bool>* node_compute;
    mutex* node_compute_mtx;

    vector<double> weight;
    double bias;

    Semaphore* a_sem;
    Semaphore* b_sem;
    Semaphore* c_sem;
};

#endif //__NODE_H__
