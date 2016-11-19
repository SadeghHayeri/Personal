#include "row.h"

void Row::clear() {
    elements.clear();
}

int Row::size() const {
    return elements.size();
}

void Row::push_back( double newElement ) {
    elements.push_back( newElement );
}

Row& Row::operator=( const Row &rRow ) {
    if( size() == rRow.size() ) {

        clear();
        for (size_t i = 0; i < rRow.size(); i++) {
            push_back( rRow[i] );
        }

    }
    else {
        throw std::length_error( "when use operator '=', two Row must have same length!" );
    }
    return *this;
}

Row& Row::operator=( const std::vector<double> &_elements ) {
    if( size() == _elements.size() ) {

        clear();
        for (size_t i = 0; i < _elements.size(); i++) {
            push_back( _elements[i] );
        }

    }
    else {
        throw std::length_error( "when use operator '=', the Row and vector must have same length!" );
    }
    return *this;
}

void Row::overWrite( const Row newRow ) {
    clear();
    elements = newRow.elements;
}

void Row::attach( const Row newRow ) {
    for (size_t i = 0; i < newRow.size(); i++)
        elements.push_back( newRow[i] );
}

Row Row::operator+( const Row &rRow ) const {
    if( size() == rRow.size() ) {

        Row newly(0);
        for (size_t i = 0; i < size(); i++) {
            newly.push_back( elements[i] + rRow[i] );
        }
        return newly;

    }
    else {
        throw std::length_error( "when use '+', left Row and right Row must have same length!" );
    }
}

Row operator*( double factor, const Row &rRow ) {

    Row newly(0);
    for (size_t i = 0; i < rRow.size(); i++) {
        newly.push_back( factor * rRow[i] );
    }
    return newly;

}

Row Row::operator/( double factor ) const {
    Row newRow;
    for (size_t i = 0; i < size(); i++)
        newRow.push_back( elements[i] / factor );
    return newRow;
}

Row& Row::operator/=( double factor ) {
    *this = *this / factor;
    return *this;
}

Row& Row::operator+=( const Row &rRow ) {
    *this = *this + rRow;
    return *this;
}

Row Row::operator-( const Row &rRow ) const {
    return *this + ( -1 * rRow );
}

Row& Row::operator-=( const Row &rRow ) {
    *this = *this + ( -1 * rRow );
    return *this;
}

std::ostream& operator<<( std::ostream& output, const Row &myRow ) {
    for (size_t i = 0; i < myRow.size() - 1; i++) {
        output << myRow[i] << '\t';
    }
    output << myRow[ myRow.size()-1 ];
    return output;
}

std::istream& operator>>( std::istream& input, Row &myRow ) {

    myRow.clear();

    std::string line;
    std::getline( input, line );

    std::stringstream mySream(line);

    double element;
    while ( mySream >> element ) {
        myRow.push_back( element );
    }
    return input;

}

double& Row::operator[]( int index ) {

    if( index > size() )
        throw std::overflow_error( "overflow when use Row[] occured!" );
    else if( index < 0 )
        throw std::underflow_error( "overflow when use Row[] occured!" );
    else {
        return elements[index];
    }

}

double Row::operator[]( int index ) const {
    Row nonConstRow = *this;
    return nonConstRow[index];
}

bool Row::operator==(  const Row &rRow ) const {

    if( size() != rRow.size() )
        return false;

    for (size_t i = 0; i < size(); i++) {
        if( elements[i] != rRow[i] )
            return false;
    }
    return true;

}

bool Row::operator==( const Matrix &rMatrix ) const {
    return rMatrix == *this;
}

Row Row::operator*( const Matrix &rMatrix ) const {

    if( size() == rMatrix.height() ) {

        Row newly;
        for (size_t i = 0; i < rMatrix.height(); i++) {
            double element = 0;
            for (size_t j = 0; j < size(); j++) {
                element += elements[j] * rMatrix[j][i];
            }
            newly.push_back( element );
        }
        return newly;

    }
    else {
        throw std::length_error( "Row width and matrix height must equal!" );
    }
}

Row& Row::operator*=( const Matrix &rMatrix ) {
    (*this).overWrite( (*this) * rMatrix );   // this = this * rMatrix
    return *this;
}
