#include <iostream> //cin, cout, endl

using namespace std;


class A{
public:
    A(){
        cout << "A Constructor" << endl;
    }
    
     virtual ~A(){
        cout << "A Destructor" << endl;
    
    }
    
    void doNothing(){
        cout << "A Method Ran" << endl;
    }

};
class B: public A{
public:
    B(){
        cout << "B Constructor" << endl;
    }
    
    virtual ~B(){
        cout << "B Destructor" << endl;
        
    }
    
    virtual void doNothing(){
        cout << "B Method Ran" << endl;
    }
    
};

class C: public B{
public:
    C(){
        cout << "C Constructor" << endl;
    }
    
    ~C(){
        cout << "C Destructor" << endl;
        
    }
    
    void doNothing(){
        cout << "C Method Ran" << endl;
    }


};

int main(){

    A* b_ptr = new B;
    A* c_ptr = new C;
    
    cout << endl << "B doNothing" << endl;
    b_ptr->doNothing();
    cout << endl << "C doNothing" << endl;
    c_ptr->doNothing();
    
    delete b_ptr;
    delete c_ptr;
}

