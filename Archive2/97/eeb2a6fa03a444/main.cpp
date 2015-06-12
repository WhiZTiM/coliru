#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

struct myObj {
    myObj someOtherOperation() {
        std::cout << "Called\n";
        return std::move(*this);   
    }
};

int main() {
    myObj().someOtherOperation().someOtherOperation();
}