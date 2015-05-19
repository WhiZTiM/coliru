#include <iostream>
#include <vector>

template <typename Container, typename Function>
void for_each(Container c, Function f){
    for(auto e : c){
		f(e);
	}
}

int main(){
    auto const cijfers = std::vector<int>{13, 33, 37};
    auto const print = [](auto e){ std::cout << e << std::endl; };
    for_each(print, cijfers);
}

