#include <type_traits>

template<typename T, std::size_t N>
struct Thing {

    template< typename... Args
#ifdef INDIRECT
	        , std::size_t ArgLen = sizeof...(Args)
	        , std::enable_if_t<ArgLen == N, int> Enable1 = 0          //works fine
#else
	        , std::enable_if_t<sizeof...(Args) == N, int> Enable1 = 0 //disables constructor
#endif
	>
	Thing(Args&&...) {}
};

int main() {
	Thing<int, 3> a { 1,2,3 };   //error C2440: 'initializing': cannot convert from 'initializer list' to 'Thing<int,3>'
	Thing<int, 3> b = { 1,2,3 }; //error C2440: 'initializing': cannot convert from 'initializer list' to 'Thing<int,3>'
}
