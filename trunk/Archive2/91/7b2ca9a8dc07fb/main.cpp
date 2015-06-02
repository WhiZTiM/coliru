#include <iostream>

struct rootNode
{
   int depth;
   int root;
};


rootNode get()
{
   rootNode returnValue;
   
   returnValue.depth = 5;
   returnValue.root  = 6;
   
   return returnValue;
}

int main()
{
   rootNode r;
   r = get();
   
   std::cout << r.depth << ' ' << r.root << '\n';
}
