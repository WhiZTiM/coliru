#include <iostream>


void f() {
 std::cout << "hello\n";   
}
int f(char const *p) {
 std::cout << "world\n";   
 return 0;
}

int main()
{
    f();
    f("you");
}
