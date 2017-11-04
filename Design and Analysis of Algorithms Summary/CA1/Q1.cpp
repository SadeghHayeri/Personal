#include <iostream>

/*
The maximum number of inversions that an
n-size ARR can have is 
    n*(n-1) / 2
*/

using namespace std;

int res[1000000];
int ARR[1000000];
int ORD[1000000];

int count_inversion_merge(int first, int last)
{
    int mid = (first+last)/2;
    int ai = first;
    int bi = mid+1;
    int final[last-first+1], final_ORD[last-first+1];
    int finali=0;
    int inversion = 0, i;

    while (ai <= mid && bi <= last) {
        if (ARR[ai] > ARR[bi]) {
                final_ORD[finali] = ORD[ai];
                final[finali++] = ARR[ai++];
        } else {
                for (int ii = ai; ii <= mid; ++ii)
                    res[ORD[ii]]++;
                final_ORD[finali] = ORD[bi];
                final[finali++] = ARR[bi++];
                inversion += mid - ai + 1;
        }
    }

    while (ai <= mid) {
        final_ORD[finali] = ORD[ai];
        final[finali++] = ARR[ai++];
    }

    while (bi <= last) {
        final_ORD[finali] = ORD[bi];
        final[finali++] = ARR[bi++];
    }

    for (i=0 ; i<last-first+1 ; i++) {
        ORD[i+first] = final_ORD[i];
        ARR[i+first] = final[i];      
    }

    return inversion;
}

int count_inversion(int a, int b)
{
    int x, y, z, mid;
    if (a >= b) return 0;

    mid = (a+b)/2;
    
    x = count_inversion(a, mid);
    y = count_inversion(mid+1, b);
    z = count_inversion_merge(a, b);

    return x+y+z;
}

int main()
{
    
    int len;

    cin >> len;
    for (int i = 0; i < len; ++i) {
        cin >> ARR[i];
        ORD[i] = i;
    }

    int inversion = count_inversion(0, len-1);
    int i;

    for (i=0 ; i<len; i++) {
            printf("%d ", len-1-i-res[i]);
    }
    printf("\n");
            
    return 0;
}