#include <iostream>


class Foo 
{
 int a;
 public:
   int getA () { return a;}
   Foo(){ a = 0;}
};

class Bar: public Foo 
{
  int b; 
  public: 
   Bar() {b = 1;} 
   int getB () { return b;}
};

void display (Foo *obj, int num) 
{
   for (int i = 0;  i < num; ++i)
   {
     std::cout << (obj+i)->getA() << std::endl;
   }
   
}

int main ()
{
	const int numElem = 3;
	Foo arrayfoo[numElem];
	display(arrayfoo, numElem);
 
	Bar arraybar[numElem];
	display (arraybar, numElem);
 
	return 0;
}