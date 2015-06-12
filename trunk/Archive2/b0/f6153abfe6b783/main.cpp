#include<iostream>

class abc{
protected:
    int x; 

public:
     void getX()
     {
          std::cout<<x;
     }
};
class b: public abc{
public :
    void something(){ x = 1;}
};

int main(){
     b objb;
     objb.something();
     objb.getX();
    }