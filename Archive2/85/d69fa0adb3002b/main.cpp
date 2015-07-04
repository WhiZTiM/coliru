/* snprintf example */
#include <stdio.h>
#include <stdint.h>
#include <iostream>
using namespace std;


class A
{
    public:
    
    A(){};
    ~A(){};
    
    uint32_t getClassId()
    {
        return(classId_);
    }

    private:
    uint32_t classId_ = 1;
    uint32_t var2_ = 11;

};

class B
{
    public:
    
    B(){};
    ~B(){};
    
    uint32_t getClassId() {return classId_;};
    
    
    private:
    uint32_t classId_ = 2;
    
};

class C
{
    public:
    C(){};
    ~C(){};
    
    A getA(){return a_; };
    B getB(){return b_; };
    
    A a_;
    B b_;
};
    
        

int main ()
{
    C c;
    A ca = c.getA();    
    uint32_t id1 = ca.getClassId();
    
    B cb = c.getB();    
    uint32_t id2 = cb.getClassId();  
    
    cout << "id1, id2 = " << id1 << "," << id2 << endl;
    
  /*
  char buffer [100];
  int cx;

  cx = snprintf ( buffer, 100, "The half of %d is %d", 60, 60/2 );

  if (cx>=0 && cx<100)      // check returned value

    snprintf ( buffer+cx, 100-cx, ", and the half of that is %d.", 60/2/2 );

  puts (buffer);
  */

  return 0;
}