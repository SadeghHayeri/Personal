#include "layer.h"

#include "semaphore.h"
#include <pthread.h>
#include <unistd.h>
#define check while

using namespace std;

Layer::Layer(int _id, int _node_num, int _input_size, Activation_function _af, bool* _initial_complete) :
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
    initial_complete(_initial_complete),
    af(_af),
    node_num(_node_num),
    nodes_added(false),
    node_compute(vector<bool>(_node_num, false))
{

    pthread_t thread;
    pthread_create(&thread, NULL, compute_core, this);

}

void Layer::set_weight(vector< vector<double> > weight) {
    while(!nodes_added);
    for (size_t i = 0; i < nodes.size(); i++)
        nodes[i]->set_weight(weight[i]);
}

void Layer::set_bias(vector<double> bias) {
    while(!nodes_added);
    for (size_t i = 0; i < nodes.size(); i++)
        nodes[i]->set_bias(bias[i]);
}

void* Layer::initial_nodes(void* arg) {
    Layer* that = (Layer*) arg;
    for (size_t i = 0; i < that->node_num; i++) {
        that->nodes.push_back(
            new Node(
                i,
                that->input_size,
                that->input,
                &that->output[i],
                that->af,
                &that->a_sem,
                &that->b_sem,
                &that->c_sem,
                that->initial_complete,
                &that->node_compute,
                &that->node_compute_mtx
            )
        );
    }
    that->nodes_added = true;
}

void* Layer::compute_core(void* arg) {
    Layer* that = (Layer*) arg;

    while (!that->is_ready());
    initial_nodes(that);

    while (true) {
        that->prev_newdata_sem->wait();
        {
            {
                that->next_read_sem->wait();
                {
                    // start computing!
                    for (size_t i = 0; i < that->nodes.size(); i++)
                        that->a_sem.signal();

                    // get all data
                    that->b_sem.wait();

                    // free all
                    for (size_t i = 0; i < that->nodes.size(); i++)
                        that->c_sem.signal();

                    // deadlock!
                    check(that->c_sem.get_value() != 0);
                }
            }
            that->read_sem.signal();
        }
        that->newdata_sem.signal();
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

void Layer::set_input(double _input[]) {
    input = _input;
}

void Layer::set_output(double _output[]) {
    output = _output;
}

Semaphore* Layer::get_newdata_sem() {
    return &newdata_sem;
}

Semaphore* Layer::get_read_sem() {
    return &read_sem;
}

void Layer::serial_compute() {
    for(Node* node : nodes)
        node->serial_compute();
}
