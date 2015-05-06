#include <iostream>
#include <cstdarg>
 
int add_nums(int count, ...) 
{
    std::cout << count << "\n";
    int result = 0;
    va_list args;
    va_start(args, count);
    std::cout << va_arg(args,int) << "\n";
    for (int i = 0; i < count; ++i) {
        std::cout << i << " " << va_arg(args, int) <<"\n";
    }
    va_end(args);
    return result;
}
 
int main() 
{
    std::cout << add_nums(0,4, 25, 25, 50, 50, 0 ,0 , 40) << '\n';
}