class Base                                                                      
{                                                                               
public:                                                                         
    static void foo() {}                                                        
    void badfoo(int i) {}                                                       
};                                                                              

template <typename T>                                                           
class Derived : public Base                                                     
{                                                                               
public:                                                                         
    void bar() { Base::foo(); }                                                 
    static void badbar() { Base::badfoo(); }  // compiles ok
    //static void badbar() { Base::badfoo(); }  // compile error                                                                                    
    //void worsebar() { Base::nonexist(); }  // compile error                                   
};                                                                              

int main()                                                                      
{                                                                               
    return 0;                                                                   
}  