#include <iostream>

template <size_t N, class T>
size_t size(T (&array)[N]) { 
    return N;
}

int main(int argc, char** argv) {
    int a[] = {1, 2, 2};
    
    std::cout << size(a) << "\n";
    return 0;
}