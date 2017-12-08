#ifndef __LAYER_H__
#define __LAYER_H__

#include <string>
#include <vector>
#include "node.h"
#include "structs.h"
#include "semaphore.h"

using namespace std;

class Layer {
public:
    Layer(int _id, int node_num, int _input_size, Activation_function af, bool* _initial_complete);

    void set_prev_newdata_sem(Semaphore* _prev_newdata_sem);
    void set_next_read_sem(Semaphore* _next_read_sem);
    void set_input(float _input[]);
    void set_output(float _output[]);
    Semaphore* get_newdata_sem();
    Semaphore* get_read_sem();

private:

    int id;

    bool* initial_complete;

    static void* compute_core(void* arg);
    bool is_ready();

    int input_size;
    vector<Node*> nodes;

    Semaphore newdata_sem;
    Semaphore read_sem;

    Semaphore a_sem;    // first nodes wait on a
    Semaphore b_sem;    // layer wait on b to ready all nodes
    Semaphore c_sem;    // nodes wait on c after complete

    Semaphore* prev_newdata_sem;
    Semaphore* next_read_sem;

    float* input;
    float* output;
};

#endif //__LAYER_H__
