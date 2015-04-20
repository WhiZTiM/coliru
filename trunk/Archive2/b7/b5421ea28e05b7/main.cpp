#include <iostream>
#include <vector>

template <typename T>
struct Data
{
    std::vector<T> data;
};

template <typename T>
struct Spec;

template <typename T, typename A>
struct Spec<std::vector<T, A>>
{
    static std::vector<T, A> Get()
    {
        return std::vector<T, A>(3);
    }
};

template <typename T>
struct Spec<Data<T>>
{
    static Data<T> Get()
    {
        return Data<T>{{T{}, T{}}};
    }
};

template <typename T>
struct Spec<Data<Data<T>>>
{
    static Data<Data<T>> Get()
    {
        return Data<Data<T>>{{{}, {}, {}, {}}};
    }
};

template <typename T>
auto Get() -> decltype(Spec<T>::Get())
{
    return Spec<T>::Get();
}

int main()
{
    std::cout << Get<Data<int>>().data.size() << std::endl;
    std::cout << Get<std::vector<int>>().size() << std::endl;
    std::cout << Get<Data<Data<int>>>().data.size() << std::endl;
}
