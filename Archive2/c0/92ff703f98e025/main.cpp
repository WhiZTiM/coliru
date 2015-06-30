
#include <unordered_map>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <queue>
using namespace std;

template<class T>
class Setting
{
    public:
    Setting(Setting* instance){((T*)instance)->write();};
    virtual void write(){cout<<"in parent\n";}
};

class child:public Setting<child>
{
  public:
   child():Setting(this){};
  virtual void write(){cout<<"in child";}
};
int main()
{
    child ch;
   
}