#include <string>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <memory>

using namespace std;

class A
{
    shared_ptr<A> parent;
   shared_ptr<A> ptr;
    vector<weak_ptr<A> > children;
public:
    A() : parent(0), name("I'm new")
    {
        }
    
    virtual ~A(){
        cout<<name<<" died"<<endl;
    }
    string name;
    virtual void setParent(shared_ptr<A> child){
        parent=child;
    }
    virtual void hello()
    {
      
      cout<<"i am "<<name<<endl;
      for(auto &i : children)
      {
        if(auto pi=i.lock()){
            pi->hello();
        }
      }
    }

};

class B : public A
{
    public:
    int numbers;
    virtual ~B(){
        cout<<name<<" died (B!)"<<endl;
    }
    virtual void hello(){
        A::hello();
         cout<<name<<" is a B!"<<endl;       
    }
    
};


int main(){
    auto a1= shared_ptr<A>(new B());
    auto a2= shared_ptr<A>(new A());
    auto a3= shared_ptr<A>(new B());
    
    a1->name="1";
    a2->name="2";
    a3->name="3";
    
    a2->setParent(a1);
    a3->setParent(a2);
      
    
//    shared_ptr<A*> a1=&a2;
    
    
    a1->hello();
    a2= shared_ptr<A>(new A());
    a1->hello();
    cout<<"done"<<endl;
    return 0;
}