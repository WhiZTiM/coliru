#include <string>
#include <iostream>

template <typename T>
struct Test
{
    std::string name()
    {
        return "none";
    }
};

#define TEST_ENABLE_TYPE(T) \
template <> \
struct Test<T> \
{ \
    std::string name() \
    { \
        static std::string n = #T; \
        return n; \
    } \
};

TEST_ENABLE_TYPE(int);
TEST_ENABLE_TYPE(float);
TEST_ENABLE_TYPE(double);

class TestClass;
TEST_ENABLE_TYPE(TestClass);

class TestClass: public Test<TestClass>
{
    
};

int main()
{
    std::cout << Test<int>().name() << std::endl;
    std::cout << Test<float>().name() << std::endl;
    std::cout << Test<double>().name() << std::endl;
    std::cout << Test<char>().name() << std::endl;
    std::cout << TestClass().name() << std::endl;
    return 0;
}