#include <vector>

template <typename T>
using v_itt = typename std::vector<T>::iterator;

template <typename T>
void foo(v_itt<T>){ }

int main() {
    typename std::vector<long>::iterator i = std::vector<long>().begin();
    foo(i);
}