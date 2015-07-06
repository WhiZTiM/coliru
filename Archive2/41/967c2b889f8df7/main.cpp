
struct TypeA {
    TypeA(int v=0) {}
};

struct TypeB {
    TypeB() {}
};

#include <boost/function.hpp>

template <typename TYPE>
struct container {
    container() = default;

    void set(boost::function<TYPE()> const& factory) { 
        _type = factory(); 
    }

    TYPE _type; // My object instance
};

#include <boost/phoenix.hpp>

int main() {
    using boost::phoenix::construct;

    container<TypeA> aCA;
    aCA.set(construct<TypeA>(1234));
    container<TypeB> aCB;
    aCB.set(construct<TypeB>());
}
