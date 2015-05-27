#include <iostream>
using namespace std;
class abc{
    public:
    static int count;
    abc(int);
    int getCount();
    private:
    int a;
  };

abc::abc(int a){
    this->a=a;
  count++;
}
int abc::getCount(){
    coutcount;
}

int abc::count = 0;

int main()
{
    abc a(2),b(4);
    cout<<"The no of object="<<b.getCount();
    cout<<"The value of a="<<abc::a;
}