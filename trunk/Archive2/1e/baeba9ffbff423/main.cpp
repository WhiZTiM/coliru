#include <string>
#include <iostream>

template<typename T, size_t R, size_t C>
void do_it(T (&arg)[R][C]) {
    for(auto& row: arg)  {
      for(T& el: row)
         std::cout << el << ' ';
      std::cout << '\n';
    }
}
int main()
{
    int x[3][2] = {1,2,3,4,5,6};
    std::string d[2][4] = {"a", "b", "c", "d", "e", "f", "g", "h"};

    do_it(x);
    do_it(d);
}
