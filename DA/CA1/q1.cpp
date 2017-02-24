#include <iostream>
#include <vector>

using namespace std;

const int size = 10000000;
int map[size];

int main() {
  cout << size << endl;
  int n;
  cin >> n;
  for (size_t i = 0; i < n; i++) {
    int c;
    cin >> c;
    for (size_t j = 0; j < c; j++) {
      int a,b,h;
      cin >> a >> b >> h;
      for (size_t k = a; k < b; k++)
        map[k] = (map[k]>h)?map[k]:h;
    }

    int see = 0;
    for (size_t j = 0; j < size; j++) {
      if(map[j] != see) {
        cout << j << " " << map[j] << " ";
        see = map[j];
      }
    }
  }
  return 0;
}
