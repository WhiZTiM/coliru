#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <iostream>
#include <sstream>

struct A {
    int i;
    
    template <typename Ar>
    void serialize(Ar& ar, const unsigned int) {
        ar & i;
    }
};

int main() {
    A a;
    a.i = 34;
    A* ap = &a;
    
    std::stringstream ss;
    boost::archive::text_oarchive out{ss};
    out << a << ap << ap;
    
    std::cout << a.i << "\n" << &a << "\n" << ap << "\n";
    
    boost::archive::text_iarchive in{ss};
    A a2;
    A* ap2;
    A* ap3;
    
    in >> a2 >> ap2 >> ap3;
    std::cout << a2.i << "\n" << &a2 << "\n" << ap2 << "\n" << ap3 << "\n";
}