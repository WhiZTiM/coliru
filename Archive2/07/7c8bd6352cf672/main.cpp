#include <iostream>
#include <functional>

template <typename Map, typename Combine, typename Arg>
auto map_combine(Map m, Combine combine, Arg arg){
	return m(arg);
}

template <typename Map, typename Combine, typename Head, typename ... Args>
auto map_combine(Map m, Combine combine, Head head, Args ... args){
	return combine(m(head), map_combine(m, combine, args ...));	
}

int main() {
    auto map = [](auto x){ return x * 2; };
    auto combine = [](auto x, auto y){ return x + y; };
    
    auto result = map_combine(map, combine, 1, 2, 3, 4, 5);
        
	std::cout << result << std::endl;
}