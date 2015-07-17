#include <iostream>
#include <utility>
#include <type_traits>
#include <typeinfo>
#include <vector>
#include <memory>
#include <limits>

template<typename T> struct visitor;

template<typename T> struct void_type
{
    using type = void;
};

// this is a common virtual base to all vistor implementations 
struct visitor_base
{
    // make polymorphic so we can dynamic_cast from this virtual base class
    virtual ~visitor_base () {}
    template<typename T>
    void visit (T & t) const
    {
        // the void_type struct is necessary to make vistor<> a dependent type of visitor_base.
        // This is necessary for late binding of visitor to the template
        dynamic_cast<visitor<typename void_type<T>::type> const&>(*this)(t);
    }
};


/////////////////////////////////////////
// Base class for all objects
/////////////////////////////////////////
class CoreBase 
{
    public:
        enum eOBJ_TYPE {TREE, CONTAINER, OBJECT};
        virtual eOBJ_TYPE GetObjType() {return OBJECT;};
        
        void AddChild(CoreBase* obj) {m_children.push_back(obj);}
        std::vector<CoreBase*>& GetChildren() {return m_children;}
        virtual void accept(visitor_base const& v) { v.visit(*this); }; // new method

    private:
        std::vector<CoreBase*> m_children;
};


/////////////////////////////////////////
//TREES
/////////////////////////////////////////

// Base class for trees -- reports its obj type as tree and defines a 
// base implementation of DoA();

// combined tree class, no generic base class necessary !!
template <typename T>
class Tree : public CoreBase
{
    public:
        eOBJ_TYPE GetObjType() { return TREE; }
        
        virtual int DoA() { return 11;}
        void accept(visitor_base const& v) { v.visit(*this); }  // new method
};

/////////////////////////////////////////
//CONTAINERS 
/////////////////////////////////////////

// Base class for containers -- reports its obj type as container, also provides DoB(), 
//which is used for all containers, and DoC(), which must be overridden by subclasses.

// combined Container class, no generic base class necessary !!
template <typename T>
class Container : public CoreBase
{
    public:
        using type = T;
        eOBJ_TYPE GetObjType() { return CONTAINER; }
        
        int DoB() { return 2; }
        int DoC();
        void accept(visitor_base const& v) { v.visit(*this); } // new method
};

// explicit specialization of method DoC for type int
template <>
int Container<int>::DoC () { return 22; }

// visitor class that implements the operations on object's children 
template <typename T>
struct visitor : virtual visitor_base
{
    template<typename U>
    void operator () (Tree<U> & t) const
    {
        printf("Performing some tree-specific logic (%d)\n", t.DoA());
    }
    template<typename U>
    void operator () (Container<U> & t) const
    {
        printf("Performing some container-specific logic (%d)\n", t.DoB() + t.DoC());
    }
    void operator () (CoreBase & t) const
    { 
        printf("Peforming some general object logic.\n");
    }
};

// This example is quite simple and does not require a set of visitor templates
// The template parameter is useful in case the pattern matching refers to a super class, in which case
// the type argument to vistor represents the dynamic type of the sub class implementing the desired API.
struct all_visitor : visitor<void> { };

void PerformCrazyFunc(CoreBase& obj)
{
    // Peform some operation on our object's children
    // The visitor packages the actual operations
    all_visitor vis;
    // notice the lack of a type switch !!
    for (auto child : obj.GetChildren())
        child->accept(vis);
}

// Driver
int main()
{
    CoreBase obj;
    obj.AddChild(new CoreBase);
    obj.AddChild(new Container<int>);
    obj.AddChild(new Tree<float>);
    PerformCrazyFunc(obj);
}
