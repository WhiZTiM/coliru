#include <thread>
#include <iostream>

void threadB() {
    std::cout << "Hello world\n";
}

void threadA() {
    std::thread B(threadB);
    B.join();

    std::cout << "Continued to run\n";
}

int main() {
    std::thread A(threadA);
    A.join(); // no difference really
}