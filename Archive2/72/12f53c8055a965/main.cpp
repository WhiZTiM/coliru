#include <iostream>
#include <string>

class BaseClass
{
public:
    // constructor
    BaseClass(const std::string& rTaskName)
        : mTaskName(rTaskName)
        , mFinished(false)
    {}

    // disable move constructor - implicitly deletes
    // the copy members: copy constructor & assignment operator
    BaseClass(BaseClass&&) = default;
    
    // the appropriate destructor chain will not be called
    virtual ~BaseClass() = default;

    // thread worker method
    void threadFunction();
protected:
    virtual int doJob(int pJob) = 0;

    // task name used for debugging
    std::string mTaskName;

    // shutdown flag
    bool mFinished;
};


class DerivedClass : public BaseClass
{
public:
    // constructor 
    explicit DerivedClass (
        const std::string& rTaskName)
        : BaseClass(rTaskName)
    {}
    
    // disable move constructor - implicitly declares
    // copy constructor and assignment operator as deleted
    DerivedClass(DerivedClass&&) = default;

    // destructor
    virtual ~DerivedClass() = default;
protected:
    // this is the worker method
    int doJob(int pJob) {
        return pJob;
    }
};


int main()
{
    DerivedClass derived1("derived1");
    DerivedClass derived2("derived2");
    DerivedClass d3(std::move(derived1));
}
