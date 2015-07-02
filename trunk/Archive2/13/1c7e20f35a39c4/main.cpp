#include <iostream>

class Matrix
{
public:
    
    using Row = float[5][6];
    Row Data[4] = {};
    // ... methods

    Row& operator[](size_t index) {
        return Data[index];
    }
};


int main() {
    Matrix m;
    m[2][3][1] = 42;
    std::cout << m.Data[2][3][1] << std::endl;
}