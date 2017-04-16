#include <algorithm>
#include <iostream>
#include <cstdlib>
using namespace std;
typedef long long ll;

const int N = 2000 * 100, Q = 4000 * 100, MAX = 1000 * 1000 * 10;

void print(int a[]) {
    cerr << '[';
    for(int i = 0; i < N - 1; ++i)
        cerr << a[i] << ", " ;
    cerr << a[N - 1] << "]" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int arr[N], ch[N];

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, MAX), dist2(1, 60000), Dis(0, 1);
    //dist: random integer number generator in range [1, MAX]
    //dist2: random integer number generator in range [1, 60000]
    //Dis: random integer number generator in range [0, 1]

    for(int i = 0; i < N; ++i)
        arr[i] = dist(rng),
        ch[i] = i;
    sort(arr, arr + N);
    random_shuffle(ch, ch + N);
    // print(ch);

    int k = dist2(rng);
    while(k & 1) k = dist2(rng);
    cerr << "k = " << k << endl;
    sort(ch, ch + k);
    // print(ch);
    // print(arr);
    for(int i = 0;i < k; i += 2)
        reverse(arr + ch[i], arr + ch[i + 1] + 1);
    // print(arr);

    cout << N << " " << Q << endl;
    int pos = 0, el = -1;
    for(int i = 0; i < Q; ++i) {
        if(el == ch[pos]) {
            while(el < ch[pos + 1])
                cout << "+ " << arr[++el] << '\n', ++i;
            pos += 2;
        }
        if(Dis(rng) && el < N - 1)
            cout << "+ " << arr[++el] << '\n';
        else {
            if(Dis(rng))
                cout << "# !" << '\n';
            else
                cout << "# ?" << '\n';
        }
        if(i >= Q) {
            cerr << "FAILED" << endl;
            cerr << "This test is incorrect." << endl;
            throw "FAILED";
        }
    }
    if(el != N - 1) {
        cerr << "FAILED" << endl;
        cerr << "This test is incorrect." << endl;
        throw "FAILED";
    }
    return 0;
}
