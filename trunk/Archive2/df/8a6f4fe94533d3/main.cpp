#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

class creature{
public:
    creature();//default constructor
    creature(int a);
    ~creature();//desconstructor 
    string getName() { return name; }
    static int getNumObjects() { return count; }
    creature(const creature& c) : 
         name(c.name), happy_level(c.happy_level) { ++count; }

    creature& operator=(const creature& c)
    {
         name = c.name;
         happy_level = c.happy_level;
         ++count;
         return *this;
    }
    
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
    cout<<"The destructor is now being called"<<endl;
    cout<<creature::getName()<<" is destroyed."<<endl;
     --count;
    cout<<"Now you have a total number of "<<creature::getNumObjects()<<" creature"<<endl;
}

int main()
{

   creature foo;//this is where the default constructor gets called which is good
   int choice = 1;
   foo=creature(choice);

   if(choice==1)
    {
        cout<<"hi"<<endl;//the destructor gets called before hi is printed out and I don't know why thats happening
    }
    cout << "There are " << creature::getNumObjects() << " objects that were created\n";
}