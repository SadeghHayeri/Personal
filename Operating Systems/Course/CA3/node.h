#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <vector>
#include <pthread.h>
#include "semaphore.h"
#include "structs.h"

using namespace std;

class Node {
public:
    Node(int _input_size, float _input[], float* _output, Activation_function _af, Semaphore* _a_sem, Semaphore* _b_sem, Semaphore* _c_sem, bool* _initial_complete);

private:
    static void* compute_core(void* arg);
    bool is_ready();

    bool* initial_complete;

    Activation_function af;

    int input_size;
    float* input;
    float* output;
    vector<float> weight;

    Semaphore* a_sem;
    Semaphore* b_sem;
    Semaphore* c_sem;
};

#endif //__NODE_H__
