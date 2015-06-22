#include <iostream>

struct data {
    
    data(int i) : i(i) {}
    
    int i;   
};

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

int main() {
    PrimeInt pi(10);
    
    std::cout << pi.get() << std::endl;
    
    OddInt oi(std::move(pi.getData()));
    
    std::cout << oi.get() << std::endl;
    
    return 0;
}