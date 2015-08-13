#include <cstdio>

namespace _
{
    template <typename T>
    class A
    {
        template <typename T2>
        class B
        {
            T2 some;
        };
    };
    
//    template<>
//    class A<int>
//    {
}



namespace _2
{
    template <typename T>
    struct A
    {
        template <typename T2>
        void foo (T2 o)
        {
            
        }
    };
    
    void test ()
    {
        A<int> a;
        a.foo ((char)'c');
//        A<int>::foo ((char)'c');
    }
    
}





template <typename T>
struct  A
{
    template <typename Ty>
    struct S
    {
        Ty m;
    };
};


// this works...  AND instantiates A<char> and A<char>::S<char>

template<>
template<>
struct A<char>::S<char> 
{
    int x;
};

//template<typename T>    // doesnt work
//struct A<int>


//template<>
//template<>
//void A<char>::foo<float> ()
//{
//}
//

//template<typename B>
//template<typename C>
//struct A<B>
//{
//   void foo<C> () {}
//};





int main ()
{
    printf ("Running\n");
    
    A<char> a;
    return 0;
    
    A<char>::S<char> obj;       // only has int x;
    obj.x = 12;
    
    A<char>::S<int> obj2;       // A<char>::S<char> gets instantiated here (first use) - 
    obj2.m = 12;             // has an int m
    
    
}

/*
    
    int   i = 12;
    float f = 13.0;
    void  *vp = 0;
    char  *cp = 0;
    
    long long ll;
    
    i = f;
    
    i = (long long)vp;
    cp = vp;
    vp = cp;
    f = vp;             // compiler error: cannot convert from void* to float
    f = (long long)vp;  // but this here - worx
    
    
    
    
    
    return 12;
}

*/