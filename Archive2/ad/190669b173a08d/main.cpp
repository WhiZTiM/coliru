#include <iostream>
using namespace std;

struct IntPtr
{
    IntPtr(int* v) : v_(v) { cout << "ctor\n"; }
    IntPtr(const IntPtr& o) : v_(o.v_) { cout << "copy ctor\n"; }
    ~IntPtr() { cout << "dtor\n"; }
    int operator*() const { cout << "deref\n"; return *v_; }
private:
    int* v_;
};

IntPtr& change(void)
{
    IntPtr x(new int(50)); // ctor
    return x; // dtor
} 
 
int main(void)
{
    IntPtr y(change()); // copy ctor
    cout << *y << endl; // deref
    return 0; // dtor
}