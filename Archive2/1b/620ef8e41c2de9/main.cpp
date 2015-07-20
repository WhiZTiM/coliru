
#include <vector>
#include <iostream>

struct BigObject {

    BigObject() : _data {1, 2, 3} 
    {}
    
 std::vector<int> _data;

};

BigObject localObj;

BigObject&&
// use this return type to solve segmentation fault:
// BigObject
foo(int n) {
    return std::move(localObj);

}

int main() {
    const auto f = foo(1);
    std::cout << f._data.size() << std::endl;
    std::cout << localObj._data.size() << std::endl;  // undefined behaviour?
    return 0;
}