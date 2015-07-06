#include <iostream>
#include <array>
#include <algorithm>


// array arithmatic
template<typename T, size_t N>
std::array<T,N> operator+ (const std::array<T,N> &as, const std::array<T,N> &bs) {
    std::array<T,N> result;
    std::transform(as.begin(), as.end(), bs.begin(), result.begin(), std::plus<T>());
    return result;
}

int main() {

    // this is fine....
    std::array<double, 3> a = {{1.1,2.2,3.3}};
    std::array<double, 3> b = {{7,8,9}};
    std::array<double, 3> c = a+b;

    for(auto i: c) {
        std::cout << i << std::endl;
    }


    // but this one fails to compile at the accumulate...
    std::vector<std::array<double,1>> data;
    data.push_back({{1}});
    data.push_back({{2}});
    data.push_back({{4}});

    std::array<double,1> sum;
    sum.fill(0.0);
    sum = std::accumulate(data.begin(),data.end(), sum);

    for(auto i: sum) {
        std::cout << i << std::endl;
    }


    return 0;
}
