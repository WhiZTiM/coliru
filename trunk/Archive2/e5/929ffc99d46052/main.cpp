#include <iostream>
#include <string>
#include <vector>

class Base{
    public:
    virtual int you() = 0;
    private:
    virtual int me() = 0;   
    };

class High:public Base{
    public:
    int me() {return 2;}
    int you() {return 3;}        
    };


int main(){
     High up;  
     std::cout << "ciao";
    
    }