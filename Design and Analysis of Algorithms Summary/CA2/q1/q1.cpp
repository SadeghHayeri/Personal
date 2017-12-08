#include <iostream>
using namespace std;

#define MAX_N 100000
#define MOD 1000000007


int k;
int mem[MAX_N+5];
int ans[MAX_N+5];

int f(int space) {
    if(mem[space] != 0)
        return mem[space];

    if(space < k)
        return 1;

    if(space == k)
        return 2;

    if(space > k) {
        int a = (f(space-k) + f(space-1)) % MOD;
        mem[space] = a;
        return a;
    }
    return -1;
}

int find_ans(int space) {
    if(space == 0)
        return 0;

    if(ans[space] != 0)
        return ans[space];

    int a = (find_ans(space-1) + f(space)) % MOD;
    ans[space] = a;
    return a;
}

int main() {
    int n;
    cin >> n >> k;

    for(int i = 0; i < n; i++) {
        int start, end;
        cin >> start >> end;

        cout << (find_ans(end) - find_ans(start-1) + MOD) % MOD << endl;
    }
}
