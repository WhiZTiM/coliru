#include <iostream>
#include <string>
#include <vector>

void a() { std::cout<<"A"; }
void b(int) { std::cout << "B"; }
enum class Enum{ X, Y };

template<typename... Args>
void c(Enum e, Args&&... args){
    switch(e){
        case Enum::X:
         a(std::forward<Args>(args)...);
        case Enum::Y:
         b(std::forward<Args>(args)...);
    }
}

int main() {
    c(Enum::Y, 3);
}
