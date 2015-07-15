#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Base {
public:
    virtual std::string getName(){
        return "Base";
    }

    virtual ~Base(){
        cout << "Base Dtor\n";
    }
};

class DynamicDerived : public Base {
public:
    std::string getName() {
        return "Derived";
    }

    ~DynamicDerived(){
        cout << "Derived Dtor\n";
    }
};

int main() {
    vector<unique_ptr<Base>> v;
    v.emplace_back(new Base());
    v.emplace_back(new DynamicDerived());
    for ( auto& e : v) {
        cout << e->getName() << "\n";
    }
    return 0;
}
