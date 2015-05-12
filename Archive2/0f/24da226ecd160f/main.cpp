#include <iostream>
#include <functional>
using namespace std;

template <typename T>
size_t f(T) {
    return sizeof(T);
}

int comb(int x, int y) {
	return x + y;
}

template <typename Map, typename Combine, typename Arg>
auto map_combine(Map map, Combine combine, Arg arg){
	return map(arg);
}

template <typename Map, typename Combine, typename Head, typename ... Args>
auto map_combine(Map map, Combine combine, Head head, Args ... args){
	return combine(map(head), map_combine(map, combine, args ...));	
}

int main() {
	std::cout << map_combine(f<int>, comb, 1,2,3) << std::endl;;
}