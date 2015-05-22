#include <type_traits>

template<typename T,
    typename std::enable_if< // Allow if
        std::is_same<T, int>::value // T == int
        , int>::type = 0>
void must_be_int(T arg) {}

int main() {
    must_be_int(4);
    
    // main.cpp:8:5: error: no matching function for call to 'must_be_int'
    // must_be_int(1.2);
    // ^~~~~~~~~~~
    // main.cpp:3:46: note: candidate template ignored: disabled by 'enable_if' [with T = double]
    must_be_int(1.2);
}