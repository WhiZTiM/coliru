#include <iostream>
#include <tuple>
using namespace std;

template<class T> struct eval; // primary template 
 
template< template<class...> class TT, class T1, class... Rest>
struct eval<TT<T1, Rest...>> {}; // partial specialization of eval
template <class T1, class T2, class T3> struct B;

int main() {
    eval<std::tuple<int, float, double>> e_tuple;
	eval<B<int, float, double>> e_B;
	return 0;
}