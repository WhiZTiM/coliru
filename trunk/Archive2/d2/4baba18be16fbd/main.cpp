#include <iostream>
#include <vector>

template <typename C, typename F>
void for_each(C const& c, F f){
    for(auto&& e : c){
		f(e);
	}
}

int main(){
    auto const cijfers = std::vector<int>{13, 33, 37};
    auto const print = [](auto e){ std::cout << e << std::endl; };
    for_each(cijfers, print);
}

