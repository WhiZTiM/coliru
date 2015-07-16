#include <iostream>
#include <vector>

#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/free.hpp>

void myFn(std::vector<float>) {std::cout << __PRETTY_FUNCTION__ << '\n';}
void myFn(std::vector<std::vector<float>>) {std::cout << __PRETTY_FUNCTION__ << '\n';}

BOOST_TYPE_ERASURE_FREE((has_myFn), myFn, 1)
using Vector = boost::type_erasure::any<has_myFn<void(boost::type_erasure::_self &)>, boost::type_erasure::_self &>;

int main() {
    bool myBool;
    std::cin >> myBool;
    
    Vector myVect = [=] {
        if (myBool) {
            std::vector<std::vector<float>> ret;
            return Vector{ret};   
        } else {
            std::vector<float> ret;
            return Vector{ret};
        }
    }();
    
    myFn(myVect);
}