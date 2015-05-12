#include <iostream>
#include <functional>
using namespace std;

template <typename T>
size_t f(T) {
    return sizeof(T);
}

struct SizeOf {
    template <typename T>
    auto operator()(T){
        return sizeof(T);
    }
};

struct Huge {
    char x[1024];
};

int comb(int x, int y) {
	return x + y;
}

template <typename Map, typename Combine, typename Arg>
auto map_combine(Map m, Combine combine, Arg arg){
	return m(arg);
}

template <typename Map, typename Combine, typename Head, typename ... Args>
auto map_combine(Map m, Combine combine, Head head, Args ... args){
	return combine(m(head), map_combine(m, combine, args ...));	
}

int main() {
    Huge x;
	std::cout << map_combine(SizeOf(), comb, 1,2,x) << std::endl;;
}