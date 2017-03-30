#include "matrix.h"

Matrix::Matrix( int rowsCount, int rowsLength ) {
    for (size_t i = 0; i < rowsCount; i++) {
        rows.push_back(Row( rowsLength) );
    }
}

Matrix::Matrix( double element ) {
    rows.push_back( Row(1, element) );
}

int Matrix::width() const {
    if( height() == 0 )
        return 0;
    else
        return rows[0].size();
}

int Matrix::height() const {
    return rows.size();
}

void Matrix::clear() {
    for (size_t i = 0; i < height(); i++)
        rows[i].clear();    // Row clear function
    rows.clear();   // vector clear function
}

void Matrix::insert( const Row &newRow, int ans ) {
    rows.insert( rows.begin() + ans, newRow );
}

void Matrix::push_back( const Row &newRow ) {
    insert( newRow, height() );
}

Matrix&  Matrix::operator=( const Matrix &rMatrix ) {
    clear();    // Matrix clear function
    for (size_t i = 0; i < rMatrix.height(); i++) {
        rows.push_back( rMatrix.rows[i] );
    }
    return *this;
}

Matrix&  Matrix::operator=( const std::vector<Row> &rMatrix ) {
    clear();    // Matrix clear function
    for (size_t i = 0; i < rMatrix.size(); i++) {
        push_back( rMatrix[i] );
    }
    return *this;
}

Matrix&  Matrix::operator=( const Row &row ) {
    clear();    // Matrix clear function
    insert( row, 0 );
    return *this;
}

Matrix& Matrix::operator=( double element ) {
    clear();
    Row newRow;
    newRow.push_back( element );
    push_back( newRow );
    return *this;
}

bool Matrix::sameSizeTo( const Matrix &rMatrix ) const {
    if( ( height() != rMatrix.height() ) || ( width() != rMatrix.width() ) )
        return false;
    return true;
}

Matrix Matrix::operator+( const Matrix &rMatrix ) const {

    if( !sameSizeTo( rMatrix ) ) {
        throw std::length_error( "when use operator '+', right Matrix and left Matrix must have same size!" );
    }

    Matrix newMatrix;
    for (size_t i = 0; i < height(); i++) {
        newMatrix.push_back( rows[i] + rMatrix.rows[i] );
    }
    return newMatrix;
}

Matrix operator*( const double factor, const Matrix &rMatrix ) {
    Matrix newMatrix;
    for (size_t i = 0; i < rMatrix.height(); i++)
        newMatrix.push_back( factor * rMatrix.rows[i] );
    return newMatrix;
}

Matrix& Matrix::operator+=( const Matrix &rMatrix ) {
    *this = *this + rMatrix;
    return *this;
}

Matrix& Matrix::operator-=( const Matrix &rMatrix ) {
    *this = *this + rMatrix;
    return *this;
}

Matrix Matrix::operator-( const Matrix &rMatrix ) const {
    return *this + ( -1 * rMatrix );
}

Row& Matrix::operator[]( const int rowNum ) {
    if( rowNum > height() ) {
        throw std::overflow_error( "overflow when use Matrix[] occured!" );
    }
    else if( rowNum < 0 ) {
        throw std::underflow_error( "overflow when use Matrix[] occured!" );
    }
    else {
        return rows[ rowNum ];
    }
}

Row Matrix::operator[]( const int rowNum ) const {
    Matrix nonConstRow = *this;
    return nonConstRow[rowNum];
}

bool Matrix::operator==( const Matrix &rMatrix ) const {
    if( ( height() != rMatrix.height() ) || ( width() != rMatrix.width() ) )
        return false;

    for (size_t i = 0; i < height(); i++) {
        if( ! (this->operator[](i) == rMatrix[i]) )
            return false;
    }
    return true;
}

bool Matrix::operator==( const Row &rRow ) const {
    if( height() > 1 )
        return false;
    if( rRow == rows[0] )
        return true;
    return false;
}

void Matrix::checkNormalMatrix() const {
    int width = rows[0].size();
    for (size_t i = 1; i < height(); i++) {
        if( width != rows[i].size() ) {
            throw std::invalid_argument( "invalid matrix!" );
        }
    }
}

std::ostream& operator<<( std::ostream& output, const Matrix &myMatrix ) {
    output << "[" << std::endl;
    for( size_t i = 0; i < myMatrix.height(); i++ )
        output << myMatrix[i] << std::endl;
    output << "]";
    return output;
}

std::istream& operator>>( std::istream& input, Matrix &myMatrix ) {

    myMatrix.clear();

    std::string line;
    std::getline( input, line );
    if( line == "[") {

        while ( line != "]" ) {

            Row newRow;
            std::getline( input, line );
            std::stringstream mySream(line);

            if( line == "]" )
                break;

            double element;
            while ( mySream >> element ) {
                newRow.push_back( element );
            }
            myMatrix.push_back( newRow );
        }
        myMatrix.checkNormalMatrix();
        return input;

    }
    else {
        throw std::invalid_argument( "bad input pattern for matrix!" );
    }
}

Matrix Matrix::operator*( const Matrix &rMatrix ) const {
    if( width() == rMatrix.height() ) {
        Matrix newMatrix;
        for (size_t i = 0; i < height(); i++) {
            newMatrix.push_back( (*this)[i] * rMatrix );
        }
        return newMatrix;
    }
    else {
        throw std::length_error( "left matrix's width must equal to right matrix's height!" );
    }
}

Matrix& Matrix::operator*=( const Matrix &rMatrix ) {
    *this = *this * rMatrix;
    return *this;
}

Matrix Matrix::operator/( const Matrix &rMatrix ) const {
    if( !square() || !sameSizeTo( rMatrix) ) {
        throw std::length_error( "when use '/', two matrix must be square and samesize!" );
    }
    return (*this) * rMatrix.invertible();
}

bool Matrix::empty() const {
    if( height() == 0 )
        return true;
    return false;
}

bool Matrix::square() const {
    if( empty() || height() != width() )
        return false;
    return true;
}

void Matrix::checkSizeForDeterminant() const {

    if( empty() ) {
        throw std::invalid_argument( "matrix is empty!" );
    }
    else if( !square() ) {
        throw std::length_error( "determinant only used for square!" );
    }

}

double roundTo( double number, int decimalCount ) {
    int newNumber = number * std::pow( 10, decimalCount );
    return newNumber / std::pow( 10, decimalCount );
}

Matrix roundTo( const Matrix myMatrix, int decimalCount ) {
    Matrix newMatrix;
    for (size_t i = 0; i < myMatrix.height() ; i++) {
        Row newRow;
        for (size_t j = 0; j < myMatrix.width(); j++)
            newRow.push_back( roundTo(myMatrix[i][j], decimalCount) );
        newMatrix.push_back( newRow );
    }
    return newMatrix;
}

Matrix Matrix::minor( int column ) const {

    Matrix sub;
    for (size_t i = 1; i < height(); i++) {
        Row tempRow;
        for (size_t j = 0; j < width(); j++)
            if( j != column )
                tempRow.push_back( (*this)[i][j] );
        sub.push_back(tempRow);
    }
    return sub;

}

double Matrix::determinant( bool checked ) const {
    // check for size only for first time
    if( !checked ) {
        checkSizeForDeterminant();
    }

    // only when one element remained
    if( width() == 1 ) {
        if( checked )
            return rows[0][0];
        else
            return roundTo( rows[0][0], ACCURACY );
    }

    else {

        double result = 0;
        for (size_t i = 0; i < width(); i++) {
            result +=  ( (i%2==0)?1:-1 ) * (operator[](0)[i]) * minor( i ).determinant( true );
        }

        if( checked )
            return result;
        else
            return roundTo( result, ACCURACY );

    }
}

void Matrix::attach( const Matrix &newMatrix ) {

    if( height() != newMatrix.height() ) {
        throw std::length_error( "error occured when attachin two matrix! (two matrix height must be equal)" );
    }

    for (size_t i = 0; i < height(); i++) {
        rows[i].attach( newMatrix[i] );
    }

}

Matrix Matrix::identityMatrix( int width ) {
    Matrix newMatrix;
    for (size_t i = 0; i < width; i++) {
        Row newRow;
        for (size_t j = 0; j < width; j++)
            newRow.push_back( (i==j)?1:0 );
        newMatrix.push_back( newRow );
    }
    return newMatrix;
}

Matrix Matrix::subMatrix( int fromX, int fromY, int toX, int toY ) {

    if ( fromX < 0 || fromY < 0 || toX > width() || toY > height() || fromX > toX || fromY > toY ) {
        throw std::invalid_argument( "error occured when use 'subMatrix' function!" );
    }

    Matrix newMatrix;
    for (size_t i = fromY; i < toY; i++) {
        Row newRow;
        for (size_t j = fromX; j < toX; j++) {
            newRow.push_back( (*this)[i][j] );
        }
        newMatrix.push_back( newRow );
    }
    return newMatrix;

}

void Matrix::swapRow( int from, int to ) {
    for (size_t i = 0; i < width(); i++)
        std::swap( rows[from][i], rows[to][i] );
}

void Matrix::fixZeroOnDiameter() {
    for (size_t i = 0; i < height(); i++)
        if( (*this)[i][i] == 0 )
            for (size_t j = 0; j < height(); j++)
                if( (*this)[j][i] != 0 )
                    (*this)[i] += (*this)[j];
}

void Matrix::checkDeterminant() const {

    checkSizeForDeterminant();

    if( determinant() == 0 ) {
        throw std::runtime_error( "determinant should not be zero!" );
    }

}

Matrix Matrix::invertible() const {

    Matrix newMatrix = *this;
    newMatrix.checkDeterminant();
    int size = newMatrix.height();

    newMatrix.attach( identityMatrix(size) );
    newMatrix.fixZeroOnDiameter();

    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            if( i != j )
                newMatrix[j] += newMatrix[j][i] / newMatrix[i][i] * -1 * newMatrix[i];

    for (size_t i = 0; i < size; i++)
        newMatrix[i] /= newMatrix[i][i];

    return roundTo( newMatrix.subMatrix( size, 0, size*2, size ), ACCURACY );

}

Matrix Matrix::operator^( int p ) const {

    if( !square() ) {
        throw std::length_error( "when use operator '^', your matrix must be square!" );
    }

    if( p == 0 )
        return identityMatrix( width() );
    else if( p < 0 )
        return (*this).invertible() ^ (p*-1);
    else {
        Matrix newMatrix = *this;
        for (size_t i = 1; i < p; i++)
            newMatrix *= *this;
        return newMatrix;
    }

}
