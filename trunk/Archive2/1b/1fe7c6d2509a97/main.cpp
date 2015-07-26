template <typename T>
struct Base
{
    template <typename S>
    Base(S x) {}
};

template <typename T>
struct Child : Base<T>
{
    using Base<T>::Base;
};

template <>
struct Child<int> : Base<int>
{
    using Base<int>::Base;
};

int main()
{
    Child<int> child(8.0f);
}