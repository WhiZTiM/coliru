#include <iostream>
#include <string>
#include <vector>

namespace Pond
{
    
    class Duck
    {
        public:
        Duck():var(0){}
        Duck(char& v):var(v){}
        char var;
    };
/*    
    template <typename M>
    class Gee
    {
        public:
        Gee(Duck& d):s_duck(d){}
        Duck& s_duck;
        M var;
    };
  */  
    template <typename M>
    class Geese
    {
        public:
        Geese(){}
        Geese(M& var):size(var){}
        M size;
    };
    
    template<typename X, typename Y>
    class Swan
    {
        public:
        Swan(X& var):z(var){}
        Geese<X> z;
        Y var;
    };
    
        class Frog
    {
    public:
        Frog():var(0){}
        short var;
    };
    
    class cls1
    {
        public:
      cls1(Duck& duck):s(duck){}
      
      Swan<Duck&, Frog> s;
    };    
/*    
    template <typename M>
    class Geese
    {
        public:
        Geese():size(0){}
        M size;
    };

    template<typename X, typename Y>
    class Swan
    {
        public:
        Geese<Duck&> z;
        X x;
        Y var;
    };

    class Frog
    {
    public:
        Frog():var(0){}
        short var;
    };


    class cls1
    {
        cls1(Toad<unsigned>& rt):t(rt)
        {}
        Swan<Duck, Frog> s;
        //Swan<Frog, Duck>& h;
        //Toad<unsigned>& t;
        //Swan<const Frog *const**const*, Duck>*** h;
        //Swan<const Frog *const**const*, Duck>* h;
//        Swan<const Frog **, Duck>* h;

//        void Jump (Toad<unsigned&&>& t)
//        {
//            return;
//        }

//        void Dive (Toad<unsigned&&>*&& t)
//        {
//            return;
//        }

//        void Swim (Toad<unsigned&&>*& t)
//        {
//            return;
//        }


    };
    */
}

template <typename T>
class Xpto
{
    public:
    T x;
};

typedef Xpto<int> Zpto;

template <typename T>
void doStuff()
{
    std::cout << 21 << std::endl;
}

template <> void doStuff<Zpto>() { std::cout << 56 << std::endl; } 

int main()
{
    Pond::Geese<int> yyy;
    using Pond::Geese<int>;
    //Pond::Duck d;
    //Pond::Gee<int> g(d);
    //Pond::cls1 ccc(d);
    Xpto<int> xxx;
    xxx.x = 34;
    doStuff<Xpto<int>>();
    
    return 0;
}
