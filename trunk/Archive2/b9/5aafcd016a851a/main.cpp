#include <iostream>
#include <memory>

struct Immutable {
    Immutable(int i) : data_{i} {}
    
    Immutable &operator=(const Immutable &other) {
        new (this) Immutable{other.data()};   
        return *this;
    }

    int data() const {return data_;}

private:
    const int data_;
};

int main() {
    Immutable i{5};
    i = Immutable{6};
    std::cout << i.data();
}