#include <iostream>
#include <memory>
#include <thread>
#include <atomic>

int main() {
    int i(0);
    
    auto lambda_a = [&i]() {
        while(i < 10) {
            std::cout << "i: " << --i << std::endl; 
        }
    };
    
    auto lambda_b = [&i]() {
       while(i < 10) {
        i += 2;
        std::cout << "    modified i: " << i  << std::endl;
       }
    };
    
    std::thread one(lambda_a);
    std::thread two(lambda_b);
    
    one.join();
    two.join();
    
    return 0;
    
    
}
    