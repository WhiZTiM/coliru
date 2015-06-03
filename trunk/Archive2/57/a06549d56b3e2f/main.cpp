#include <iostream>
#include <type_traits>
#include <array>
#include <vector>
#include <string>
template< class... >  struct voider{ using type = void; };
template< class...Ts>  using void_t= typename voider<Ts...>::type;
using namespace std;
template <class T, class = void>
struct Print{
 void operator()(T&elem){
        cout<<elem<<endl;
 }
};
template <class T> 
struct Print < T, void_t<decltype(begin(declval<T&>())),decltype(end(declval<T&>()))>>{
    void operator()(T&container){
        for(auto&elem:container)
            cout<<elem<<" ";
        cout<<endl;
    }
};
template<class T>
void print(T&&t){
    Print<T>()(forward<T>(t));
}

 int main() 
{  
    auto a = {1.3, 2.8, 0., 5.8};
    auto v = vector<string>{"un"s,"deux"s};
    auto s = "trois"s;
    auto i = 101;
    print(a);
    print(v);
    print(s);
    print(i);
}