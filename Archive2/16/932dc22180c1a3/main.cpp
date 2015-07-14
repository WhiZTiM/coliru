#include <iostream>
#include <utility>
#include <type_traits>
#include <typeinfo>
#include <vector>
#include <memory>

// Forward reference vistor implementation, in this case to handle containers based on CRTP.
// At this point visitor<T> are incomplete classes, but we can still call methods on them 
// inside the vistor_base template since they are dependent variables inside the template.
// We can do this because dependent variables are not actually bound until instantiation time, 
// i.e., inside main(). At that point we will have the complete class. 
template<typename T> struct visitor;

// this is a common virtual base to all vistor implementations 
struct visitor_base
{
    // make polymorphic so we can dynamic_cast from this virtual base class
    virtual ~visitor_base () {}
    // This is the base visit method that the accept methods on containers will call with 
    // the argument `*this`. The method deduces the type of the calling class through template 
    // param T. This allows us to dynamic_cast down to subclass vistor<T>. Note that this pattern is 
    // an implementation of virtual template methods, which the C++ language does not otherwise 
    // support.
    template<typename T>
    void visit (T & t) const
    {
        // decay_t removes ref and cv, which is necessary because
        // T is deduced as &, or const&, but we want to cast to visitor<T>
        dynamic_cast<visitor<std::decay_t<T>> const&>(*this)(t);
    }
};

// Though not strictly necessary, these pure virtual methods in the core base class will enforce
// vistor pattern compliance.
struct CoreBase
{
    virtual void accept(visitor_base const& v) = 0;
    // `this` pointer is const in const method 
    virtual void accept(visitor_base const& v) const = 0;
};

// These are the container dummies. When one uses the visitor pattern, there is no need to have a 
// non-template base class for type recognition. In this example, I implemented const and 
// non-const methods. One could also implement & and && qualified methods (C++11). the appropriate
// vistor<T> will call these methods as implemented by the user.
template<typename impl> struct ContainerTypeA : CoreBase
{ 
    void ApiForContainerTypeA()
    {
        std::cout << "called ApiForContainerTypeA" << std::endl;
    }
    void ApiForContainerTypeAConst() const
    {
        std::cout << "called ApiForContainerTypeAConst" << std::endl;
    }
};
template<typename impl> struct ContainerTypeB : CoreBase
{
    void ApiForContainerTypeB()
    {
        std::cout << "called ApiForContainerTypeB" << std::endl;
    }
    void ApiForContainerTypeBConst() const
    {
        std::cout << "called ApiForContainerTypeBConst" << std::endl;
    }
};

// These are the derived class container implementations. Each user class must have accept methods
// conforming to these definitions. The accept methods pass the caller's type to visitor_base, which 
// in turn passes to vistor<T>. Note that *this is a const & in a const method.
struct ContainerImplA : ContainerTypeA<ContainerImplA>
{
    void accept(visitor_base const& v) { v.visit(*this); }
    void accept(visitor_base const& v) const { v.visit(*this); }
};

struct ContainerImplB : ContainerTypeB<ContainerImplB>
{
    void accept(visitor_base const& v) { v.visit(*this); }
    void accept(visitor_base const& v) const { v.visit(*this); }
};

// This is the vistor<T> template. Here is where the actual calls into the container api's will occur.
// vistor uses overload resolution to select the appropriate method for  the specfic container.
// Note that I have not implemented a return types on the container calls. However, one could implement
// a templatized return value, which would need to pass through the accept methods on the containers.
// This class should have at least one void operator () (T & t) method per visited type.

template <typename T>
struct visitor : virtual visitor_base
{
    template<typename impl>
    void operator () (ContainerTypeA<impl> & t) const
    {
        std::cout << "lvalue ref method ";
        static_cast<T&>(t).ApiForContainerTypeA();
    }
    template<typename impl>
    void operator () (ContainerTypeB<impl> & t) const
    {
        std::cout << "lvalue ref method ";
        static_cast<T&>(t).ApiForContainerTypeB();
    }
    template<typename impl>
    void operator () (ContainerTypeA<impl> const& t) const
    {
        std::cout << "const lvalue ref method ";
        static_cast<T const&>(t).ApiForContainerTypeAConst();
    }
    template<typename impl>
    void operator () (ContainerTypeB<impl> const& t) const
    {
        std::cout << "const lvalue ref method ";
        static_cast<T const&>(t).ApiForContainerTypeBConst();
    }
};

// This is the derived vistor class that will be passed to the accept methods. It multiply derives from 
// any number of vistor<T> implementations. There should be one base class per visted type.
struct container_visitor : visitor<ContainerImplA>, visitor<ContainerImplB> { };

// Driver
int main()
{
    using namespace std;
    container_visitor vis;

    // test const objects
    vector<shared_ptr<const CoreBase>> vec;
    vec.push_back(make_shared<ContainerImplA>());
    vec.push_back(make_shared<ContainerImplB>());
    for (auto p : vec) p->accept(vis);

    // test non-const object
    vector<shared_ptr<CoreBase>> vecc;
    vecc.push_back(make_shared<ContainerImplA>());
    vecc.push_back(make_shared<ContainerImplB>());
    for (auto p : vecc) p->accept(vis);
}
