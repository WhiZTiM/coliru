#include <iostream>

//Base data structure to encapsulate only data.
struct data {
    data(int i) : i(i) {}
    
    int i;   
};

//Wrapper around our data structure, with interfaces to access
//the values and the data; implement your own constructor to
//gate the value
class PrimeInt {
public:
    PrimeInt(const int i)
    : d(i) {}

    PrimeInt(const data& other)
    : d(other) {}
    
    PrimeInt(data&& other)
    : d(std::move(other)) {}
    
    PrimeInt& operator=(const PrimeInt&) = default;
    PrimeInt& operator=(PrimeInt&&) = default;
    
    int get() {return d.i;};
    data& getData() {return d;}

private:
    data d;
};

//Wrapper around our data structure, with interfaces to access
//the values and the data; implement your own constructor to
//gate the value
class OddInt {
public:
    OddInt(const int i)
    : d(i) {}

    OddInt(const data& other)
    : d(other) {}
    
    OddInt(data&& other)
    : d(std::move(other)) {}
    
    OddInt& operator=(const OddInt&) = default;
    OddInt& operator=(OddInt&&) = default;
    
    int get() {return d.i;};
    data& getData() {return d;}

private:
    data d;
};

//Notice that we can even use std::move with a value if we wish.
//This is much easier than casting, as we can pass around resources
//from an object. Even better (or worse), you could use pointers (but this is
//another story).
int main() {
    PrimeInt pi(10);
    
    std::cout << pi.get() << std::endl;
    
    OddInt oi(std::move(pi.getData()));
    
    std::cout << oi.get() << std::endl;
    
    return 0;
}