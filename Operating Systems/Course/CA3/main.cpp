// thread01.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include <array>

#include "layer.h"
#include "semaphore.h"
#include "network.h"

#include <pthread.h>

using namespace std;

float khodesh(float x) {
    return x;
}

int main() {

    vector<int> layers_node_num = {1, 5, 1};
    vector<Activation_function> layers_af = {khodesh, khodesh, khodesh};

    Network nn(layers_node_num, layers_af);

    vector< vector<float> > input;
    vector<float> tmp = {1, 2, 3};
    input.push_back(tmp);
    input.push_back(tmp);
    input.push_back(tmp);
    input.push_back(tmp);

    vector< vector<float> > output = nn.run(input);

    for( auto v : output ) {
        for( auto i : v ) {
            cout << i << " ";
        }
        cout << endl;
    }

    cout << "oooooooo" << endl;
}
