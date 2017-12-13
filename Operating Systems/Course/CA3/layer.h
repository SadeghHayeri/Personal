#ifndef __LAYER_H__
#define __LAYER_H__

#include <string>
#include <vector>
#include <mutex>
#include "node.h"
#include "structs.h"
#include "semaphore.h"

using namespace std;

class Layer {
public:
    Layer(int _id, int _node_num, int _input_size, Activation_function af, bool* _initial_complete);

    void set_prev_newdata_sem(Semaphore* _prev_newdata_sem);
    void set_next_read_sem(Semaphore* _next_read_sem);
    void set_input(double _input[]);
    void set_output(double _output[]);
    Semaphore* get_newdata_sem();
    Semaphore* get_read_sem();

    void set_weight(vector< vector<double> > weight);
    void set_bias(vector<double>);

    void serial_compute();

private:

    int id;

    Activation_function af;
    int node_num;

    bool* initial_complete;

    static void* initial_nodes(void* arg);
    static void* compute_core(void* arg);
    bool is_ready();
    bool nodes_added;

    int input_size;
    vector<Node*> nodes;

    Semaphore newdata_sem;
    Semaphore read_sem;

    Semaphore a_sem;    // first nodes wait on a
    Semaphore b_sem;    // layer wait on b to ready all nodes
    Semaphore c_sem;    // nodes wait on c after complete

    vector<bool> node_compute;
    mutex node_compute_mtx;

    Semaphore* prev_newdata_sem;
    Semaphore* next_read_sem;

    double* input;
    double* output;
};

#endif //__LAYER_H__
