#ifndef DENSEMATRIX_H_
#define DENSEMATRIX_H_

#include <cstddef>
#include <iostream>
#include <utility>

class DenseMatrix {
    private:
        size_t m_ = 0, n_ = 0;
        double *values = nullptr;
    public:
        /* ctor */
        DenseMatrix( size_t, size_t );
        /* copy ctor */
        DenseMatrix( const DenseMatrix& rhs );
        /* move ctor */
        DenseMatrix( DenseMatrix&& rhs ) noexcept;
        /* copy assignment */
        const DenseMatrix& operator=( const DenseMatrix& rhs );
        /* move assignment */
        const DenseMatrix& operator=( DenseMatrix&& rhs ) noexcept;
        /* matrix multiplication */
        DenseMatrix operator*( const DenseMatrix& rhs ) const;
        /* dtor */
        ~DenseMatrix();
};

#endif

/* ctor */
DenseMatrix::DenseMatrix( size_t m, size_t n ) :
    m_( m ), n_( n ) {
    std::cout << "ctor with two arguments called. " << this << std::endl;
    if ( m_*n_ > 0 )
        values = new double[ m_*n_ ];
}

/* copy ctor */
DenseMatrix::DenseMatrix( const DenseMatrix& rhs ) :
    m_( rhs.m_ ), n_( rhs.n_ ) {
    std::cout << "copy ctor called. " << this << std::endl;
    if ( m_*n_ > 0 ) {
        values = new double[ m_*n_ ];

        std::copy( rhs.values, rhs.values + m_*n_, values);
    }
}

/* move ctor */
DenseMatrix::DenseMatrix( DenseMatrix&& rhs ) noexcept :
    m_( rhs.m_ ), n_( rhs.n_ ), values( rhs.values ) {
    std::cout << "move ctor called. " << this << std::endl;
    rhs.values = nullptr;
}

/* copy assignment */
const DenseMatrix& DenseMatrix::operator=( const DenseMatrix& rhs ) {
    std::cout << "copy assignment called. " << this << std::endl;

    if ( this != &rhs ) {
        if ( m_*n_ != rhs.m_*rhs.n_ ) {
            delete[] values;
            values = new double[ rhs.m_*rhs.n_ ];
        }

        m_ = rhs.m_;
        n_ = rhs.n_;
        std::copy( rhs.values, rhs.values + m_*n_, values);
    }

    return *this;
}

/* move assignment */
const DenseMatrix& DenseMatrix::operator=( DenseMatrix&& rhs ) noexcept {
    std::cout << "move assignment called. " << this << std::endl;

    m_ = rhs.m_;
    n_ = rhs.n_;
    delete[] values;
    values = rhs.values;
    rhs.values = nullptr;

    return *this;
}

/* matrix multiplication */
DenseMatrix DenseMatrix::operator*( const DenseMatrix& rhs ) const {
    return DenseMatrix( this->m_, rhs.n_ );
}

/* dtor */
DenseMatrix::~DenseMatrix() {
    std::cout << "dtor called. " << this << std::endl;
    delete[] values;
}

#include <iostream>
#include <utility>
//#include "densematrix.h"

int main( int argc, char* argv[] ) {
    /* ctor */
    DenseMatrix A( 5, 10 );
    std::cout << "&A " << &A << std::endl;
    std::cout << "--------------------1\n";
    /* ctor */
    DenseMatrix B( 10, argc );
    std::cout << "&B " << &B << std::endl;
    std::cout << "--------------------2\n";
    /* copy ctor */
    DenseMatrix C = A;
    std::cout << "&C " << &C << std::endl;
    std::cout << "--------------------3\n";
    /* copy assignment */
    C = B;
    std::cout << "--------------------4\n";
    /* move ctor */
    DenseMatrix D( A*B );
    std::cout << "&D " << &D << std::endl;
    std::cout << "--------------------5\n";
    DenseMatrix E = DenseMatrix( 100, 200 );
    std::cout << "&E " << &E << std::endl;
    std::cout << "--------------------6\n";
    /* move assignment */
    D = C*D;
    std::cout << "--------------------7\n";

    return 0;
}
