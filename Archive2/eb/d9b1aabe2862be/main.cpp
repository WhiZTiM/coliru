template<typename T>
struct TypeAttribute
{
    T m_Type;
};

template<typename T>
struct TypeAttribute2
{
    using Type = typename T::Type;
    Type  m_Type;
};

struct Foo : TypeAttribute<Foo::Type>
{
    enum class Type
    {
        Type1
    };
};

struct Bar : TypeAttribute2<Bar>
{
    enum class Type
    {
        Type1
    };
};
