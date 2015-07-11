#include <vector>
#include <iostream>

template<typename Type>
struct Arguments {

    template<class... Args>
    Arguments(Args... tail)
    {
        Build(tail...);
    }

    template<class T, class... Args>
    void Build(T head, Args... tail) 
    { 
        contents.push_back(head); 
        Build(tail...);
    }

    template<class T>
    void Build(T head)
    { 
        contents.push_back(head); 
    }

    void Build() {}
    
    operator std::vector<Type>() { return contents; }

    std::vector<Type> contents;

};

void test(const std::vector<int> args = std::vector<int>())
{
    for (auto& arg : args) {
        std::cout << arg << std::endl;
    }
}

template <typename... Args>
void foo(Args&&... args)
{
    test(Arguments<int>(args...));
}

int main()
{
    foo(0, 1, 2, 3, 4, 5);
    return 0;
}