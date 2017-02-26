#ifndef _ROW_H_
#define _ROW_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <exception>
#include <stdexcept>
#include "matrix.h"
class Matrix;

#define ACCURACY 3

class Row {
public:

    Row() {};
    Row( int length, double element = 0 ) : elements(length,element) {};
    Row( const std::vector<double> &_elements ) : elements(_elements) {};

    void overWrite( const Row newRow );
    void push_back( double newElement );
    void attach( const Row newRow );
    void clear();

    Row& operator=( const Row &rRow );
    Row& operator=( const std::vector<double> &_elements );

    Row operator+( const Row &rRow ) const;
    Row& operator+=( const Row &rRow );

    Row operator-( const Row &rRow ) const;
    Row& operator-=( const Row &rRow );

    Row operator*( const Matrix &rMatrix ) const;
    Row& operator*=( const Matrix &rMatrix );

    Row operator/( double factor ) const;
    Row& operator/=( double factor );

    double& operator[]( int index );
    double operator[]( int index ) const;
    int size() const;

    bool operator==(  const Row &rRow ) const;
    bool operator!=(  const Row &rRow ) const { return !(operator==(rRow)); }
    bool operator==( const Matrix &rMatrix ) const;
    bool operator!=( const Matrix &rMatrix ) const { return !(operator==(rMatrix)); }

    friend Row operator*( double factor, const Row &rRow );
    friend std::ostream& operator<<( std::ostream& out, const Row &myRow );
    friend std::istream& operator>>( std::istream& input, Row &myRow );

private:
    std::vector<double> elements;
};

Row operator*( double factor, const Row &rRow );
std::ostream& operator<<( std::ostream& output, const Row &myRow );
std::istream& operator>>( std::istream& input, Row &myRow );

#endif /* _ROW_H_ */
