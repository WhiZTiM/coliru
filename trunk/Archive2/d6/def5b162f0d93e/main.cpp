#include <iostream>

template<typename T, typename S>
struct SomeRandomClass
{
    int myInt = 42;
};

// concept to test for whether some type is SomeRandomClass<T,S>
template<typename T>
struct is_random_class : std::false_type{};

template<typename T, typename S>
struct is_random_class<SomeRandomClass<T,S>> : std::true_type{};

// non-templated class
class MyNonTemplatedClass
{
    
    public:
    template<typename T>
    void DoSomething(T & t) 
    {
       DoSomethingHelper(t, typename is_random_class<T>::type());
    }
    
    private:
    //use tag dispatch. If the compiler is smart it won't actually try to instantiate the second param
    template<typename T>
    void DoSomethingHelper(T&t, std::true_type)
    {
        std::cout << "Called DoSomething with SomeRandomClass whose myInt member has value " << t.myInt << std::endl;
    }
    
    template<typename T>
    void DoSomethingHelper(T&t, std::false_type)
    {
        std::cout << "Called DoSomething with a type that is not SomeRandomClass\n";
    }
};

int main()
{
    SomeRandomClass<int, int> a;
    
    MyNonTemplatedClass b;
    b.DoSomething(a); // calls specialization
    
    double c = 3.14;
    b.DoSomething(c); // does not call specialization
    
    return 0;
}
