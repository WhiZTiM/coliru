#include <iostream>
#include <functional>
#include <memory>
#include <vector>

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
    std::vector<std::shared_ptr<void>> v;
    {
        auto a = std::make_shared<SomeThing>();
        auto b = std::make_shared<FooBar>();
        v.emplace_back(std::move(a));
        v.emplace_back(std::move(b));
    }
    cout << "\nDestructing the vector...\n";
}
