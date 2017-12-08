#include "layer.h"

#include "semaphore.h"
#include <pthread.h>
#include <unistd.h>

using namespace std;

Layer::Layer(int _id, int node_num, int _input_size, Activation_function af, bool* _initial_complete) :
    id(_id),
    input_size(_input_size),
    read_sem(Semaphore(1)),
    newdata_sem(Semaphore(0)),
    prev_newdata_sem(NULL),
    next_read_sem(NULL),
    input(NULL),
    output(NULL),
    a_sem(Semaphore(0)),
    b_sem(Semaphore(0)),
    c_sem(Semaphore(0)),
    initial_complete(_initial_complete) {

    for (size_t i = 0; i < node_num; i++)
        nodes.push_back( new Node(input_size, input, &output[i], af, &a_sem, &b_sem, &c_sem, initial_complete) );

    pthread_t thread;
    pthread_create(&thread, NULL, compute_core, this);

}

void* Layer::compute_core(void* arg) {
    Layer* that = (Layer*) arg;

    while (!that->is_ready());

    while (true) {
        cout << that->id << "*layer: waiting for new data ..." << endl;
        that->prev_newdata_sem->wait();
        {
            cout << that->id << "*layer: new data recived ..." << endl;
            // that->read_sem.wait();
            {
                // cout << that->id << "*layer: get input mutex ..." << endl;
                that->next_read_sem->wait();
                {
                    cout << that->id << "*layer: get output mutex ..." << endl;

                    // start computing!
                    for (size_t i = 0; i < that->nodes.size(); i++)
                        that->a_sem.signal();

                    // get all data
                    for (size_t i = 0; i < that->nodes.size(); i++)
                        that->b_sem.wait();

                    // free all
                    for (size_t i = 0; i < that->nodes.size(); i++)
                        that->c_sem.signal();

                    cout << that->id << "*layer: data ready!" << endl;

                }
                // that->next_read_sem->signal();
                // cout << that->id << "*layer: signal next_read_sem ..." << endl;
            }
            that->read_sem.signal();
            cout << that->id << "*layer: signal read_sem ..." << endl;
        }
        that->newdata_sem.signal();
        cout << that->id << "*layer: signal newdata_sem ..." << endl;
    }
    return NULL;
}

bool Layer::is_ready() {
    return *(initial_complete);
}

void Layer::set_prev_newdata_sem(Semaphore* _prev_newdata_sem) {
    prev_newdata_sem = _prev_newdata_sem;
}

void Layer::set_next_read_sem(Semaphore* _next_read_sem) {
    next_read_sem = _next_read_sem;
}

void Layer::set_input(float _input[]) {
    input = _input;
}

void Layer::set_output(float _output[]) {
    output = _output;
}

Semaphore* Layer::get_newdata_sem() {
    return &newdata_sem;
}

Semaphore* Layer::get_read_sem() {
    return &read_sem;
}
