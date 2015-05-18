#include <iostream>
#include <type_traits>

struct trivial 
{ 
    trivial() = default; 
    trivial(trivial const&) = default; // or even trivial& 
    trivial(trivial&&) = delete; 
}; 
struct nontrivial 
{ 
    nontrivial() = default; 
    nontrivial(nontrivial const&) {} 
}; 

struct enclosing 
{ 
    static constexpr int i = {}; 
    static constexpr trivial t = {}; 
    static constexpr nontrivial n = {}; 
}; 

auto j = enclosing::i; // l-t-r applied? 
auto u = enclosing::t; // l-t-r applied? 
auto m = enclosing::n; // l-t-r applied?

int main()
{
}