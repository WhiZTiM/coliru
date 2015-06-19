#include <iostream>

template<typename T>
struct Counter
{
    static uint const index;
};


struct SharedCount
{
    template<typename T>
    static uint getNext()
    {
        uint c = counter;
        counter++;

        return c;
    }

    static uint counter;
};

uint SharedCount::counter = 0;


template<typename T>
uint const Counter<T>::index(SharedCount::getNext<T>());


int main()
{
    std::cout << Counter<float>::index << std::endl;
    std::cout << Counter<float>::index << std::endl;
    std::cout << Counter<int>::index << std::endl;
    std::cout << Counter<double>::index << std::endl;

    return 0;
}
