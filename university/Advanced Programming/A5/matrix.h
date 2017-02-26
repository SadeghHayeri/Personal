#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>
#include <exception>
#include <stdexcept>
#include "row.h"
class Row;

class Matrix {
public:

    Matrix() {};
    Matrix( int rowsCount, int rowsLength );
    Matrix( const std::vector<Row> &_rows ) : rows(_rows) {};
    Matrix( double element );

    void push_back( const Row &newRow );
    void insert( const Row &newRow, int ans );
    void attach( const Matrix &newMatrix );      // attach from right
    void clear();

    void swapRow( int from, int to );
    void fixZeroOnDiameter();                    // remove zero in diameter ( used for "invertible()" )
    void checkDeterminant() const;               // check matrix square and not zero ( used for "determinant()" )
    void checkSizeForDeterminant() const;        // check for empty and square matrix ( used for "checkDeterminant()" )
    void checkNormalMatrix() const;              // check matrix for normal size and row width ( used for get input from std io )

    int height() const;
    int width() const;
    bool empty() const;
    bool square() const;
    bool sameSizeTo( const Matrix &rMatrix ) const;
    double determinant( bool checked = false ) const;
    Matrix invertible() const;
    Matrix minor( int column ) const;
    Matrix subMatrix( int fromX, int fromY, int toX, int toY );

    Matrix& operator=( const Matrix &rMatrix );
    Matrix& operator=( const std::vector<Row> &rMatrix );
    Matrix& operator=( const Row &row );
    Matrix& operator=( double element );

    Matrix operator+( const Matrix &rMatrix ) const;
    Matrix& operator+=( const Matrix &rMatrix );

    Matrix operator-() const { return -1 * (*this); }
    Matrix operator-( const Matrix &rMatrix ) const;
    Matrix& operator-=( const Matrix &rMatrix );

    Matrix operator*( const Matrix &rMatrix ) const;
    Matrix& operator*=( const Matrix &rMatrix );

    Matrix operator/( const Matrix &rMatrix ) const;

    Row& operator[]( const int rowNum );
    Row operator[]( const int rowNum ) const;

    bool operator==( const Matrix &rMatrix ) const;
    bool operator==( const Row &rRow ) const;

    Matrix operator^( int p ) const;

    static Matrix identityMatrix( int width );

    friend Matrix operator*( const double factor, const Matrix &rMatrix );
    friend std::ostream& operator<<( std::ostream& output, const Matrix &myMatrix );
    friend std::istream& operator>>( std::istream& input, Matrix &myMatrix );

private:
    std::vector<Row> rows;
};

Matrix operator*( const double factor, const Matrix &rMatrix );
std::ostream& operator<<( std::ostream& output, const Matrix &myMatrix );
std::istream& operator>>( std::istream& input, Matrix &myMatrix );

#endif /* _MATRIX_H_ */
