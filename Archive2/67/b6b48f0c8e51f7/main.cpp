#include <thread>
#include <iostream>

void test (){
    std::cout << "Ok";
}

int main () {
    std::thread t1(test);
    t1.join();
    return 0;
}