#include "node.h"

#include <pthread.h>
#include <iostream>
#include "semaphore.h"

#include <ctime>
#include <unistd.h>

using namespace std;

Node::Node(int _input_size, float _input[], float* _output, Activation_function _af, Semaphore* _a_sem, Semaphore* _b_sem, Semaphore* _c_sem, bool* _initial_complete) :
    input_size(_input_size),
    input(_input),
    output(_output),
    af(_af),
    a_sem(_a_sem),
    b_sem(_b_sem),
    c_sem(_c_sem),
    weight(vector<float>(_input_size, 1)),
    initial_complete(_initial_complete)
{

    pthread_t thread;
    pthread_create(&thread, NULL, compute_core, this);

}

void* Node::compute_core(void* arg) {

    cout << "> thread start!\n";
    Node* that = (Node*) arg;

    while (!that->is_ready());

    while (true) {
        // sleep(1);
        cout << "$node: WAITING...\n";
        that->a_sem->wait();
        cout << "$node: FREE...\n";

        // sleep(1);
        //TODO:...
        // float result = 0;
        // for (size_t i = 0; i < that->input_size; i++)
        //     result += that->input[i];
        // result /= that->input_size;
        // *(that->output) = result;

        cout << "$node: computing compelete...\n";

        that->b_sem->signal();
        cout << "$node: signal b\n";

        // sleep(1);

        that->c_sem->wait();
        cout << "$node: free from c\n";
    }
    return NULL;
}

bool Node::is_ready() {
    return *(initial_complete);
}
