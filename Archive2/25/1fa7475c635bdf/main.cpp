#include <iostream>

class MyObject {
public:
    MyObject(int i)
    : n(i) {
        std::cout << "i've initialized n to i before this: " << n << std::endl;
    }
private:
    int n;
};

int main() {
    MyObject obj(3);
    
    return 0;
}