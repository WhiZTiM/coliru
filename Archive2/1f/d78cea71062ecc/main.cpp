#include <iostream>
#include <cstdlib>
#include <cassert>
 
#define ASSERT_EQ(a, b) assert_eq(a, b, __FILE__, __LINE__)

template <typename T1, typename T2>
void assert_eq(const T1 & a, const T2 & b, const char * file, int line) {
    using T = typename std::common_type<T1, T2>::type;
    
    if (static_cast<T>(a) != static_cast<T>(b)) {
        std::cout << "assertion failed at " << file << ":" << line << ": " << a << " != " << b << "\n";
    	std::abort();
    }
}

int main() {
	int x = 42;
	unsigned long long y = 123;
    assert(x == 42);
    assert(y == 123);
	ASSERT_EQ(x, 42);
	ASSERT_EQ(y, 123);
}