#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

struct myObj {
    myObj& someOtherOperation() {
        std::cout << "Called\n";
        return *this;   
    }
};

int main() {
    myObj& ref = myObj().someOtherOperation().someOtherOperation();
}