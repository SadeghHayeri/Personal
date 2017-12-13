#include "node.h"

#include <pthread.h>
#include <iostream>
#include "semaphore.h"

#include <ctime>
#include <unistd.h>

using namespace std;

Node::Node(int _id, int _input_size, double _input[], double* _output, Activation_function _af, Semaphore* _a_sem, Semaphore* _b_sem, Semaphore* _c_sem, bool* _initial_complete, vector<bool>* _node_compute, mutex* _node_compute_mtx) :
    id(_id),
    input_size(_input_size),
    input(_input),
    output(_output),
    af(_af),
    a_sem(_a_sem),
    b_sem(_b_sem),
    c_sem(_c_sem),
    weight(vector<double>(_input_size, 1)),
    bias(0),
    initial_complete(_initial_complete),
    node_compute(_node_compute),
    node_compute_mtx(_node_compute_mtx)
{

    pthread_t thread;
    pthread_create(&thread, NULL, compute_core, this);

}

void Node::set_weight(vector<double> _weight) {
    weight = _weight;
}

void Node::set_bias(double _bias) {
    bias = _bias;
}

void* Node::compute_core(void* arg) {

    Node* that = (Node*) arg;
    while (!that->is_ready());

    while (true) {
        that->a_sem->wait();

        double result = that->bias;
        for (size_t i = 0; i < that->input_size; i++)
            result += that->input[i] * that->weight[i];
        *(that->output) = that->af(result);

        that->node_compute_mtx->lock();
        (*that->node_compute)[that->id] = true;
        that->node_compute_mtx->unlock();

        that->check_all_computed();
        that->c_sem->wait();
    }
    return NULL;
}

void Node::check_all_computed() {
    node_compute_mtx->lock();

    for (int i = 0; i < node_compute->size(); i++)
        if((*node_compute)[i] == false) {
            node_compute_mtx->unlock();
            return;
        }

    // if all complete!
    for (int i = 0; i < node_compute->size(); i++)
        (*node_compute)[i] = false;
    b_sem->signal();
    node_compute_mtx->unlock();
}

bool Node::is_ready() {
    return *(initial_complete);
}

void Node::serial_compute() {
    double result = bias;
    for (size_t i = 0; i < input_size; i++)
        result += input[i] * weight[i];
    *output = af(result);
}
