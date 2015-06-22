#include <string>

using namespace std::literals;

template <class T>
struct Lol {
    using truc = int;
};

template <>
struct Lol<double> {
    using truc = std::string;
};

template <class T>
void f(typename Lol<T>::truc &) {}
    
int main() {
    f(4);
    f("Hello"s);
}
