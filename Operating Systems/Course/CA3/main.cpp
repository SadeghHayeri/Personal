#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <fstream>
#include <ctime>

#include "layer.h"
#include "semaphore.h"
#include "network.h"

using namespace std;

double LINIER(double x) {
    return x;
}

double TANH(double x) {
    return tanh(x);
}

int main() {

    ///////////////////// LAYER 1
    vector<double> b1;
    b1 = {
        -64.662792988884348,
        55.166473202056522,
        -164.65949834408667,
        15.211160979463422,
        12.24130356452798,
        17.021888846682156,
        -27.158230855968867,
        4.6294220239768293,
        2.599812799324801,
        -140.22968989032836
    };

    vector< vector<double> > w1;
    vector<double> tmp;

    tmp = {0.47033493164029083, 1.4098429917984185, -0.45868250608443023};
    w1.push_back(tmp);
    tmp = {9.6050793142547, -4.8106381377184553, -6.2203249699239107};
    w1.push_back(tmp);
    tmp = {31.770859194938183, -5.7448922199483343, -16.587627795598152};
    w1.push_back(tmp);
    tmp = {-0.84940531846430345, 0.992233239423821, -1.0016216732907082};
    w1.push_back(tmp);
    tmp = {-31.627591279841969, 6.372163860709442, 16.370799951110723};
    w1.push_back(tmp);
    tmp = {-54.424139618749813, 18.259089064353208, 28.641186983131369};
    w1.push_back(tmp);
    tmp = {-0.79810901615687035, 1.4504845684255849, -2.1005592298494506};
    w1.push_back(tmp);
    tmp = {-0.4491767869239795, 0.029756397265863002, -0.13040976475951177};
    w1.push_back(tmp);
    tmp = {-0.0095618922693373482, -0.033137398429464504, 0.00097940644650935786};
    w1.push_back(tmp);
    tmp = {23.972375584069319, 1.39315413638509, -0.74824486890357866};
    w1.push_back(tmp);


    ///////////////////// LAYER 2
    vector<double> b2;
    b2 = {-52.815634642162856};

    vector< vector<double> > w2;
    tmp = {
        -2.0210328911392796,
        1.4925632391411969,
        0.44033520941192872,
        -1.1474388699560774,
        -0.84731807564734474,
        -0.44500692998149916,
        -0.54580535770972349,
        1.2629238917177057,
        29.750097611943637,
        -11.125476345495747
    };
    w2.push_back(tmp);

    ///////////////////// INPUT
    fstream f;
    f.open("InputFile.txt");
    vector< vector<double> > input;
    double input_tmp;
    while (f >> input_tmp) {
        vector<double> tmp_vec;
        tmp_vec.push_back(input_tmp);

        f >> input_tmp;
        tmp_vec.push_back(input_tmp);

        f >> input_tmp;
        tmp_vec.push_back(input_tmp);

        input.push_back(tmp_vec);
    }

    vector<int> layers_node_num = {3, 10, 1};
    vector<Activation_function> layers_af = {LINIER, TANH, LINIER};

    ////////////////////////////////////////////////////////////////////////////

    Network nn(layers_node_num, layers_af);

    nn[1]->set_weight(w1);
    nn[1]->set_bias(b1);

    nn[2]->set_weight(w2);
    nn[2]->set_bias(b2);


    // parallel
    clock_t p_start = clock();
    vector< vector<double> > p_output = nn.parallel_compute(input);
    clock_t p_end = clock();

    // serial
    clock_t s_start = clock();
    vector< vector<double> > s_output = nn.serial_compute(input);
    clock_t s_end = clock();

    ////////////////////////////////////////////////////////////////////////////

    cout << "parallel: " << 1000.0 * (p_end-p_start) / CLOCKS_PER_SEC << "ms" << endl;
    cout << "serial: " << 1000.0 * (s_end-s_start) / CLOCKS_PER_SEC << "ms" << endl;
    cout << "speed up: " << (float)(s_end-s_start) / (p_end-p_start) << endl;

    for (size_t i = 0; i < p_output.size(); i++) {
        cout << setprecision(15);
        cout << s_output[i][0] << " - " << p_output[i][0] << endl;
    }
}
