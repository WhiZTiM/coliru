#include <iostream>

template<class T>
void test() {
    T v1 = 12345678901234567890ULL;
    T v2 = 12345678901234567891ULL;
    std::cout << ((v1==v2) ? "" : "not") << "equal\n";
}

int main()  {
    test<double>();
    test<unsigned long long>();
}