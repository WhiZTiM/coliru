#include <iostream>
#include <functional>

std::function<int()> lambda_func() {
    return []{ return 112; };
}

int main(){
    std::cout << lambda_func()();
}