namespace N
{
    template <typename T>
    class Foo {
        static const T bar;
    };
}

namespace O
{
    typedef N::Foo<int> Baz;

    template<>
    const int Baz::bar = 1;
}

int main() {
    
}