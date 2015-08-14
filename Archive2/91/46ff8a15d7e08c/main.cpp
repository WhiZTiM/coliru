#include <iostream>
#include <typeinfo>

template<class...>
struct type_list {};

template<class... Ts>
auto make_type_list(Ts&&...)
{
    return type_list<Ts...>();
}

template<class X, class Y>
constexpr bool isSameT(X, Y)
{
    return std::is_same<X, Y>::value;
}

template<class DerivedT>
struct NodeBase {
    enum { inputStream };
    enum { outputStream };

    static constexpr auto getTypes(decltype(inputStream)) {
        return type_list<>();
    }

    static constexpr auto getTypes(decltype(outputStream)) {
        return type_list<>();
    }

    static constexpr auto takes()
    {
        return takesImpl<DerivedT>();
    }

    static constexpr auto gives()
    {
        return givesImpl<DerivedT>();
    }

private:
    template<class T>
    static constexpr auto takesImpl(
        std::enable_if_t<isSameT(inputStream, T::inputStream)>* = 0)
    {
        return make_type_list();
    }

    template<class T>
    static constexpr auto takesImpl(
        std::enable_if_t<!isSameT(inputStream, T::inputStream)>* = 0)
    {
        return make_type_list(T::inputStream);
    }

    template<class T>
    static constexpr auto givesImpl(
        std::enable_if_t<isSameT(inputStream, T::inputStream)>* = 0)
    {
        return make_type_list();
    }

    template<class T>
    static constexpr auto givesImpl(
        std::enable_if_t<!isSameT(inputStream, T::inputStream)>* = 0)
    {
        return make_type_list(T::inputStream);
    }
};

template<int Y>
struct StreamType {};

template<class Tag=void>
struct Node : public NodeBase<Node<Tag>> {
    enum { inputStream };
    enum { outputStream };

    static constexpr auto getTypes(decltype(inputStream)) {
        return type_list<int>();
    }

    static constexpr auto getTypes(decltype(outputStream)) {
        return type_list<double>();
    }

    // takes/gives list automagically defined for us
};

template<class X, class Y>
void printTypes(const X& x, const Y& y)
{
    std::cout << typeid(x.getTypes(y)).name() << std::endl;
}

int main()
{
    Node<> x;
    printTypes(x, x.inputStream);
    printTypes(x, x.outputStream);
}