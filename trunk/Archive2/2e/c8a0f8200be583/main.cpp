#include <iostream>
#include <string>
#include <vector>

template< typename T>
std::string getName() { return "Unknown"; }

template<>
std::string getName()<unsigned char> { return "unsigned"; }

template<>
std::string getName()<signed char> {return "signed";}

template<>
std::string getName()<int> {return "int";}

template < typename ... Args >
struct Tuple {
    typedef void HeadRaw;
    typedef Tuple<> Tail;
    static void print() { printf("Empty\n"); }
};

template <typename T, typename ... Args >
    struct Tuple<T,Args...> {
    typedef T HeadRaw;
    typedef Tuple<Args...> Tail;
    static void print() { printf("%s\n", getName<HeadRaw>().c_str());
                          Tail.print(); }
};

int main(***) {
    Tuple<int,char> a;
    a::print();
}

// Writes:
// int
// Unknown
// Empty

// Adding the following:
template< typename T>
std::string getName<char> {return "char";}

// changes to the following:
// int
// char
// Empty

/*
int main()
{
    char v = 'x';               // Simple.
    char * p = & v;             // Works, No issue here.
    const char * cp = & v;      // Works. No problem yet.
    cp = p;                     // Works fine
    char ** pp = & p;           // Still ok.
    //const char ** cpp = & p;    // HUGE HORRIFYING BARF

    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
*/