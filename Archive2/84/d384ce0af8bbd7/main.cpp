#include <string>
#include <iostream>


class Test
{
public:
    Test();
    static constexpr int MIN_VALUE { 5 };
    int m_otherValue = 10;
};

Test::Test()
{
    m_otherValue = std::max(m_otherValue, MIN_VALUE);
}

int main()
{
    Test t;
}