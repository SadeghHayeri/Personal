#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <string>
#include <vector>
#include "structs.h"
#include "semaphore.h"
#include "layer.h"

using namespace std;

class Network {
public:
    Network(vector<int> layers_node_num, vector<Activation_function> layers_af);
    vector< vector<float> > run(vector< vector<float> > _input);
private:

    static void* input_core(void* arg);
    static void* output_core(void* arg);
    bool initial_complete;

    vector<Layer*> layers;

    Semaphore first_newdata_sem;
    Semaphore* first_read_sem;

    Semaphore* last_newdata_sem;
    Semaphore last_read_sem;

    int input_size;
    int output_size;

    float* input;
    float* output;

    vector< vector<float> > tmp_input;
    vector< vector<float> > tmp_output;
};

#endif //__NETWORK_H__
