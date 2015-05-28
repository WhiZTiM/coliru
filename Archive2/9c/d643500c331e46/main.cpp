#include <array>
#include <utility>

    template <class T, std::size_t N, class GenType, std::size_t... I> 
    constexpr std::array<T, N>
make_array_impl (GenType gen, std::index_sequence <I...>) 
{
    return {{ gen (I)... }};
}

    template <class T, std::size_t N, class GenType> 
    constexpr std::array<T, N>
make_array (GenType gen)
{
    return make_array_impl <T, N> (
            gen, 
            std::make_index_sequence <N> {}
    );
}

    constexpr int
generator_const (std::size_t /* index */)
{
    return 1;
}

    constexpr auto
a = make_array <int, 3> (generator_const);

static_assert (a.size () == 3, "");
static_assert (a[0] == 1, "");
static_assert (a[1] == 1, "");
static_assert (a[2] == 1, "");

int main () {}