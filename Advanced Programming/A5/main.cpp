#include <iostream>
#include "matrix.h"
#include "row.h"

using namespace std;

int main(int argc, char* argv[]) {
  Matrix m;
	
  Row r(4);
	r[0]=2;
	r[1]=3;
	r[2]=4;
	r[3]=7;
  
	vector<Row> rows(3, r);
  
	m = Matrix(rows);
  
	r[2]=-10;
  
	m.insert(r,m.height());
	m[3][0]=-5;
	m[0][1]=0.1;
	m[1][3]=6.5;
	
  cout << "row:\t" << r << endl;
	cout << "matrix:\t" << endl << m << endl;
	cout << "matrix[0][1]:\t" << m[0][1] << endl;
	cout << "determinant:\t" << m.determinant() << endl;
  
  return 0;
}
