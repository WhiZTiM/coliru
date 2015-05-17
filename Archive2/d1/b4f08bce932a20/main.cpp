#include <vector>
using namespace std;

class A
{
   public:
      A(int){}
};

class B
{
   vector<A> va; //Error no default constructor available
public:
   B(vector<A>v):va(v)
   {}
};

int main()
{
    vector<A> v;
    B b(v);
}
