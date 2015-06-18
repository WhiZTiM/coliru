#include <iostream>
#include <memory>

using namespace std;

namespace NRs {
class Base {

public:
    virtual ~Base() {}

    // Factory for Base class

    static shared_ptr<Base> FromDatatoolObject(const int& i);
    
    virtual void SayHi() = 0;
    
};

class Derived1 : public Base {

public:
    
    Derived1(const int& i) : m_i(i){}

    void SayHi() { cout << "I am Derived1 with value " << m_i << endl; }

private:
    int m_i;
    
};

} //NRs

namespace NAsn1 {
    
class Derived2 : public NRs::Derived1 {

public:
    friend NRs::Base; // Allow Base to construct


    void SayHi() { cout << "I am Derived2 with value " << m_i << endl; }

private:
    Derived2(const int& i) : Derived1(i+10), m_i(i){}

    int m_i;
    
};
} //NAsn1




shared_ptr<NRs::Base> NRs::Base::FromDatatoolObject(const int& i) {
    cout << "Create a sub-class of Base" << endl;
    return make_shared<NAsn1::Derived2>(i);
}



int main(){
    cout << "I'm creating with value 2." << endl;
    auto d2 = NRs::Base::FromDatatoolObject(2);
    d2->SayHi();
            
    return 0;
}