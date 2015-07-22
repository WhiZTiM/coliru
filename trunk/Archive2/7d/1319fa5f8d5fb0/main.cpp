#include <string>
#include <iostream>

template<typename T, size_t SIZE>
void ReadArray(T (&input)[SIZE]) {
    std::string str( input, input + SIZE);
    std::cout << str << std::endl;
}

int main() {
    char foo[] = "test";
    ReadArray(foo);
}