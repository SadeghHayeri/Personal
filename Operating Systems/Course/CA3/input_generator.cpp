#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {

    srand (time(NULL));

    for (size_t i = 0; i < 54; i++) {
        int num = rand() % 10 + 1;
        cout << num << " ";
    }

}
