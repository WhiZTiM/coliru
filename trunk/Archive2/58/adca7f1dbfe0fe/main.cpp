#include <algorithm>

template <class T>
struct id_ {
    using type = T;
};

template <class T>
using id = typename id_<T>::type;

template <class Integer, class T, class Ite>
unsigned runLengthEncodingCompressBytes(Ite begin, Ite end, Integer T::*const field, id<Integer> marker)
{
    return 0;
}
 
template <class Integer, class T, class Ite>
unsigned runLengthEncodingDecompressBytes(Ite begin, Ite end, Integer T::*const field, id<Integer> marker)
{
    return 0;
}

struct Foo {
    char i;
};

int main() {
    Foo truc[10]{};
    runLengthEncodingCompressBytes(std::begin(truc), std::end(truc), &Foo::i, 0);
    runLengthEncodingDecompressBytes(std::begin(truc), std::end(truc), &Foo::i, 0);
}