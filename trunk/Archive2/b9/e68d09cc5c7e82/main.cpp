#include <iostream>
#include <vector>

struct input_iterator_tag {};
struct output_iterator_tag {};

struct InputIter {
    typedef input_iterator_tag iterator_category;
};

struct OutputIter {
    typedef output_iterator_tag iterator_category;
};

template<class T>
class Vector {
public:
    explicit Vector(size_t, T=T());

    template <class InputIt,
              decltype(input_iterator_tag(typename InputIt::iterator_category{}))* = nullptr>
    Vector(InputIt, InputIt)
    {
        std::cout << "input iterator overload called" << std::endl;
    }
};

template<class T>
Vector<T>::Vector(size_t, T)
{
    std::cout << "size_t overload called" << std::endl;
}

int main(int argc, char* argv[])
{
    InputIter input;
    OutputIter output;

    Vector<int> a(0U, 0);
    Vector<int> b(input, input);
    // Should fail to compile:
    Vector<int> c(output, output);
}
