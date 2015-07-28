    #include <cstdio>
    #include <iostream>
    #include <chrono>
    #include <vector>
    #include <forward_list>
    #include <typeinfo>
    
    using namespace std;
    
    #define getType(val) std::decay_t<decltype(val)>
    
    template<class Self>
    struct Trait1{
        void trait1_dispatch_test(){
            static_cast<typename Self::Parent::template mix< getType(*this) >&>(*this).dispatch_test();
        }
    };
    
    template<class _Parent>
    struct A1_wrap{
        using Parent = _Parent;
        using Self = A1_wrap<Parent>;
    
        template<class Caller>
        struct mix : Trait1<A1_wrap> {
            
            void dispatch_test(){
                cout << "A1 dispatch_test " << typeid(Caller).name() << endl;
            }
            void A1_call_parent(){
                //reinterpret_cast<typename Self::Parent::template mix< getType(*this) >&>(*this).root_call();            // THIS WORKS
                static_cast<typename Self::Parent::template mix< getType(*this) >&>(*this).root_call();               // THIS IS NOT
            }
        };
    };
    
    template<class _Parent >
    struct A2_wrap{
        using Parent = _Parent;
        using Self = A2_wrap<Parent>;
    
        template<class Caller>
        struct mix : A1_wrap< A2_wrap >::template mix<Caller> {                         // WORK if replace Caller with void
            void root_call(){
                cout << "root_call" << endl;
                cout << "called from " << typeid(Caller).name() << endl;
            }
        };
    };
    
    
    
    int main()
    {
        A2_wrap<void>::mix<void> a2;
        a2.A1_call_parent();
     
        return 0;
    }
    