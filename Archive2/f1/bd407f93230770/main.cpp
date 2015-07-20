
#include <vector>
#include <iostream>

struct BigObject {

    BigObject() : _data {1, 2, 3} 
    {}
    
 std::vector<int> _data;

};


BigObject&&
// use this return type to solve segmentation fault:
// BigObject
foo(int n) {

    BigObject localObj;

    return std::move(localObj);

}

int main() {

    const auto & f = foo(1);
    std::cout << f._data.size() << std::endl;
    return 0;
}