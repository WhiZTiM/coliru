#include <cstddef>

using array = int[];

template<std::size_t N>
void foo(int const(&)[N]) {}

int main()
{
    // candidate template ignored: couldn't infer template argument 'N'
    // foo({ 0, 1, 2, 3 });
    foo(array { 0, 1, 2, 3 });
}
