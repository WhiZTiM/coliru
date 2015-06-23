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
    
    operator data() {return d;};

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
    
    operator data() {return d;};

private:
    data d;
};

//Notice that we can now implicitly cast from one type to another.
int main() {
    PrimeInt pi(10);
    
    std::cout << pi.get() << std::endl;
    
    OddInt oi(pi);
    
    std::cout << oi.get() << std::endl;
    
    return 0;
}