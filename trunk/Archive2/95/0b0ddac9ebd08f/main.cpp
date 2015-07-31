#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct EnConst
{
    unsigned num_bits;
    bool is_signed;
    
union //RecordType    // Declare a simple union type
{
    char   ch;
    int    i;
    long   l;
    float  f;
    double d;
    int *int_ptr;
};

    //RecordType t;

};


int main()
{
    EnConst e;
    
    //e.t.i = 5;
    e.i = 5;
    
    //RecordType t;
    //t.i = 5; // t holds an int
    //t.f = 7.25 // t now holds a float 
    
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
