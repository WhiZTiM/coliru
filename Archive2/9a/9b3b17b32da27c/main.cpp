#include <iostream>

using namespace std;

void what_the_foo1() {
    const unsigned val = 5;
    unsigned* ptr = const_cast<unsigned*>(&val);
    *ptr = 7;
    cout << "val(" << &val << "): " << val << " and value of ptr(" << ptr << "): " << *ptr << endl; 
}

void what_the_foo2() {
    unsigned val = 5;
    unsigned* ptr = &val;
    *ptr = 7;
    cout << "val(" << &val << "): " << val << " and value of ptr(" << ptr << "): " << *ptr << endl; 
}

int main() {
    what_the_foo1();
    what_the_foo2();
}
