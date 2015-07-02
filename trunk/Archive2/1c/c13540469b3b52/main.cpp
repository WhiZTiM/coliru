#include <iostream>
#include <string>
#include <tuple>
#include <set>

struct Base {
    Base(const int& rIntVal,  const std::string& rStrVal)
        : mIntVal(rIntVal)
        , mStrVal(rStrVal)
    {}
    inline bool operator<(const Base& rhs) const {
        return std::tie(mIntVal, mStrVal) < std::tie(rhs.mIntVal, rhs.mStrVal);
    }
private:    
    int mIntVal;
    std::string mStrVal;
};

struct Derived : public Base {
    Derived(
        const int& rIntVal, 
        const std::string& rStrVal, 
        const std::string& rOtherStrVal,
        const std::string& rOtherStrVal1)
        : Base(rIntVal, rStrVal)
        , mOtherStrVal(rOtherStrVal)
        , mOtherStrVal1(rOtherStrVal1)
    {}
    inline bool operator<(const Derived& rhs) const {
        // not sure what to do here - this is my best guess???
        if( Base::operator<(rhs) ) {
            return std::tie(mOtherStrVal, mOtherStrVal1) < 
                std::tie(rhs.mOtherStrVal, rhs.mOtherStrVal1);
        } else {
            return false;
        }
    }
private:    
    std::string mOtherStrVal;
    std::string mOtherStrVal1;
};

int main()
{
    Base b1(1, "base");
    Base b2(1, "base1");
    Derived d1(2, "baseStr", "derived1Str", "derived2Str");
    Derived d2(2, "baseStr", "derived1Str1", "derived2Str2");
    std::set<Derived> foo = {d1, d2};
}
