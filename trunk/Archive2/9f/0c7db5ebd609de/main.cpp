#include <iostream>
#include <string>

class obj{
    int x;
public:
    obj(int n) {x=n;}
    inline void printM() { std::cout << x << "\n"; }
};

int main()
{
   obj p(2);
   obj x = 4;
   x.printM();
   obj h[] = { 3, 4, 2 };
   h[2].printM();
   return 0;
}
