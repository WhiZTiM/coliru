#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

class creature{
public:
    creature();//default constructor
    creature(int a);
    creature(const creature& c) : 
         name(c.name), happy_level(c.happy_level) 
         { 
             std::cout << "Copy constructor called" << endl;
             ++count; 
         }
    ~creature();//desconstructor 
    string getName() { return name; }
    static int getNumObjects() { return count; }
    
private:
    static int count;
    string name;
    int happy_level;
};

int creature::count=0;//initialize static member variable

creature::creature(){//default constructor
    name="bob";
    ++count;

    cout<<"The default constructor is being called"<<endl;
}

creature::creature(int a)
{
    ++count;
    cout << "The int constructor is begin called" << endl;
    if(a==1)
    {
        name="billybob";

    }


    else if(a==2)
    {
        name="bobbilly";

    }

    else if(a==3)
    {
        name="bobbertyo";
        happy_level=1;
    }
}

creature::~creature()
{
    cout<<"Now you have a total number of "<<creature::getNumObjects()<<" creatures before destruction"<<endl;
    cout<<"The destructor is now being called"<<endl;
     --count;
    cout<<"Now you have a total number of "<<creature::getNumObjects()<<" creatures after destruction"<<endl;
}


int main()
{

   creature foo;//this is where the default constructor gets called which is good
   int choice = 1;
   foo=creature(choice);
   creature foo2 = foo;
}