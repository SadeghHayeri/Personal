#include <iostream>
#include <cstring>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

using namespace std;

unsigned long long ARR[10000000];
unsigned long long M1[10000000];
unsigned long long M2[10000000];

unsigned long long find_max(unsigned long long arr[], unsigned long long index, unsigned long long max_dic[]) {
	unsigned long long mm = max_dic[index];
	if(mm != -1)
		return mm;
	return max_dic[index] = max( arr[index-1] + find_max(arr, index-2, max_dic), find_max(arr, index-1, max_dic) );
}

int main() {
	unsigned long long n;
	
	cin >> n;
	for (unsigned long long i = 0; i < n; ++i) {
		cin >> ARR[i];
	}

	if(n == 1) {
		cout << ARR[0] << endl;
		return 0;
	}

	memset(M1, -1, 10000000);
	memset(M2, -1, 10000000);

	M1[0] = 0;
	M1[1] = ARR[0];
	M2[0] = 0;
	M2[1] = ARR[1];

	cout << max( find_max(ARR, n-1, M1), find_max(ARR+1, n-1, M2) ) << endl;
}