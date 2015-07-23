#include <iostream>
#include <map>
#include <set>
#include <typeinfo>
#include <string>
#include <memory>

class TestClass {
    std::unique_ptr<int> sp;
public:

    void setTester_Way1(std::unique_ptr<int> te) {
         auto deleter=std::move(sp);
         sp=std::move(te);
    }
    
    void setTester_Way2(std::unique_ptr<int> te) {
         sp=std::move(te);
}
};

int main()
{
    TestClass t;
    auto p = std::make_unique<int>(10);
    t.setTester_Way2(p);
}