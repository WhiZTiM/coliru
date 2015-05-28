#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/vector_sparse.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace ublas = boost::numeric::ublas;

int main()
{
    ublas::compressed_matrix<double, ublas::column_major, 0> Matrix A(5, 5, 12);

    A(0, 0) =  2.; A(0, 1) =  3.;
    A(1, 0) =  3.; A(1, 2) =  4.; A(1, 4) =  6.;
    A(2, 1) = -1.; A(2, 2) = -3.; A(2, 3) =  2.;
    A(3, 2) =  1.;
    A(4, 1) =  4.; A(4, 2) =  2.; A(4, 4) =  1.;

    ublas::vector<double> y(5);
    y(0) =  8.;
    y(1) = 45.;
    y(2) = -3.;
    y(3) =  3.;
    y(4) = 19.;

    ublas::permutation_matrix<size_t> pm(A.size1());
    lu_factorize(A, pm);
    lu_substitute(A, pm, y);

    std::cout << y << std::endl; // output: [5](1,2,3,4,5)
}
