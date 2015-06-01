#include <iostream>
#include <string>
#include <vector>

#include <iostream>
using namespace std;
class Base
{
   public:
        virtual ~Base()
        {
            cout<<"in Base"<<endl;
        }    
};

class drived : public Base
{

    public:
        virtual ~drived()
        {
            cout <<"in drived"<<endl;
          }
};


int main()
{
    Base * base = new drived[10];
    delete [] base;
}
