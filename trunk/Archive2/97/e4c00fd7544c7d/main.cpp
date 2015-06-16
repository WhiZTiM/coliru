#include <iostream>

int main() {
    
    char highLeftCorner = 201; // faudrait-il utiliser un wchar_t ou un truc du genre ?
    char mysterious = 65;
    std::cout << highLeftCorner << std::endl; // le caractère qui pose problème.
    std::cout << mysterious << std::endl; // et celui qui n'en pose pas.
    
    return 0;

}