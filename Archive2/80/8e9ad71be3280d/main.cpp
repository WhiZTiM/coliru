#include <iostream>
#include <set>

using namespace std;

class foo {
  public:
    foo() { cout << "foo()" << endl; }
    foo(const foo& other) { cout << "foo(const foo other)" << endl; }
};

void bar(const foo& f) {
    std::set<foo> seq{f};
}

int main() {
    foo f;
    
}   
