#include <iostream>
#include <boost/any.hpp>

using std::cout;

struct SomeThing {
    SomeThing() { cout << "SomeThing() "; }
    SomeThing(SomeThing const &) { cout << "SomeThing(const &) "; }
    SomeThing(SomeThing &&) { cout << "SomeThing(&&) "; }
    ~SomeThing() { cout << "~SomeThing() "; }
};
struct FooBar {
    FooBar() { cout << "FooBar() "; }
    FooBar(FooBar const &) { cout << "FooBar(const &) "; }
    FooBar(FooBar &&) { cout << "FooBar(&&) "; }
    ~FooBar() { cout << "~FooBar() "; }
};

int main() {
    std::vector<boost::any> v;
    v.push_back(SomeThing{});
    v.push_back(FooBar{});
    cout << "\nDestructing the vector...\n";
}