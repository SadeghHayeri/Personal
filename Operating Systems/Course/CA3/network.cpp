#include "network.h"
#include <ctime>
#include <unistd.h>
#include <cstring>

Network::Network(vector<int> layers_node_num, vector<Activation_function> layers_af) :
    first_newdata_sem(Semaphore(0)),
    first_read_sem(NULL),
    last_read_sem(Semaphore(1)),
    last_newdata_sem(NULL),
    initial_complete(false) {

    input_size = layers_node_num[0];
    output_size = layers_node_num[layers_node_num.size()-1];

    input = new float[layers_node_num[0]];
    output = new float[layers_node_num[layers_node_num.size()-1]];

    for (size_t i = 1; i < layers_node_num.size(); i++)
        layers.push_back( new Layer(i, layers_node_num[i], layers_node_num[i-1], layers_af[i], &initial_complete) );

    Semaphore* tmp;

    tmp = &first_newdata_sem;
    for (size_t i = 0; i < layers.size(); i++) {
        layers[i]->set_prev_newdata_sem(tmp);
        tmp = layers[i]->get_newdata_sem();
    }
    last_newdata_sem = tmp;

    tmp = &last_read_sem;
    for (int i = layers.size()-1; i >= 0; i--) {
        layers[i]->set_next_read_sem(tmp);
        tmp = layers[i]->get_read_sem();
    }
    first_read_sem = tmp;


    for (size_t i = 0; i < layers_node_num.size(); i++) {
        float* middle_arr = new float[layers_node_num[i]];
        memset(middle_arr, 0, layers_node_num[i]);

        if(i == 0)
            input = middle_arr;

        if(i == layers_node_num.size()-1)
            output = middle_arr;

        if(i != layers_node_num.size()-1)
            layers[i]->set_input(middle_arr);

        if(i != 0)
            layers[i-1]->set_output(middle_arr);
    }

    initial_complete = true;
}

vector< vector<float> > Network::run(vector< vector<float> > _input) {
    tmp_input = _input;

    pthread_t input_thread, output_thread;
    pthread_create(&input_thread, NULL, input_core, this);
    pthread_create(&output_thread, NULL, output_core, this);

    void* out;
    pthread_join(output_thread, &out);

    return tmp_output;
}

void* Network::input_core(void* arg) {
    sleep(1);
    Network* that = (Network*) arg;

    for(auto data : that->tmp_input) {
        that->first_read_sem->wait();
        cout << "# input: get mutex\n";
        {
            for (size_t i = 0; i < that->input_size; i++)
                that->input[i] = data[i];
        }
        // that->first_read_sem->signal();
        // cout << "# input: signal mutex\n";

        cout << "# signal newdata\n";
        (that->first_newdata_sem).signal();

    }

    return NULL;
}

void* Network::output_core(void* arg) {
    Network* that = (Network*) arg;

    for (size_t i = 0; i < that->tmp_input.size(); i++) {
        that->last_newdata_sem->wait();
        cout << "= output: newdata recived\n";
        // that->last_read_sem.wait();
        // cout << "= output: get mutex\n";
        {
            vector<float> tmp;
            for (size_t i = 0; i < that->output_size; i++)
                tmp.push_back(that->output[i]);
            that->tmp_output.push_back(tmp);
        }
        that->last_read_sem.signal();
        cout << "= output: signal mutex\n";

    }

    cout << "OUTPUT COMPLETE!\n";

    return NULL;
}
