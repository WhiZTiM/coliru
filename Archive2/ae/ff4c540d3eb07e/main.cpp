#include <tr1/memory>
#include <iostream>

int main()
{
    std::auto_ptr<int> p;
    std::auto_ptr<int> pp;
    std::cout << __GLIBCXX__ << '\n';
}
