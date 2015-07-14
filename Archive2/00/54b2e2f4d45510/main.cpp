#include <string>
#include <stdio.h>

int main() {
    char* f = nullptr;
    std::string s;
    if (f != nullptr) {
        s += f;
    }
    printf("Old string: %s\n", s.data());
    
    f = (char*) "hello world";
    if (f != nullptr) {
        s += f;
    }
    printf("New string: %s\n", s.data());
}