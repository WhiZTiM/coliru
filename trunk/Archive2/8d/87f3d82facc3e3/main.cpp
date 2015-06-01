#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

using Work = std::vector<std::function<void()>>;

void begin(Work const& work) 
{
    for(auto const f : work)
    {        
        f();
    }
}

void test(Work work) 
{
    begin(work);
}

int main() 
{
    test({ []{std::cout << "Hi!\n";}, });
    test({ []{std::cout << "Bye\n";}, });
}
