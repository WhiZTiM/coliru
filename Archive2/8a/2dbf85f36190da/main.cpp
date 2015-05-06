#include <iostream>

using namespace std;

struct A
{
    A operator+(A const& a) const { cout << 1 << endl; return A(); }
    A& operator++() { cout << 2 << endl; return *this; }
    A operator++(int) const { cout << 3 << endl; return *this; }
    bool operator!() const { cout << 4 << endl; return true; }
    
};

A operator+(A const& a, A const& b) { cout << 5 << endl; return A(); }
A& operator++(A& a) { cout << 6 << endl; return a; }
A operator++(A const& a, int) { cout << 7 << endl; return A(); }
bool operator!(A const& a) { cout << 8 << endl; return false; }

int main()
{
    A a, b;
    
    a + b;
    ++a;
    a++;
    !a;
    
    return 0;
}

