#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/traits/c_array.hpp>
#include <boost/numeric/ublas/assignment.hpp>

namespace ublas = boost::numeric::ublas;

int main() {
    using V = ublas::c_vector<int, 3>;

    V v;
    v <<= 1,2,3;

    for (auto i : v)
        std::cout << i << " ";
}
