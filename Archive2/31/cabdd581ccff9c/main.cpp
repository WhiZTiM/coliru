#include <memory>
#include <cstdio> 

struct X {
    X()  { puts(__PRETTY_FUNCTION__); }
    ~X() { puts(__PRETTY_FUNCTION__); }
};

int main() {
    X obj;

    // watch this:
    obj.~X();
    new(&obj) X;
    
    // no need to manually call the destructor
}
