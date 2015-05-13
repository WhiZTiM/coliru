#include <string>
#include <iostream>
 
template <class F, class G>
auto compose0(const F& f, const G& g)
{
 return [&f, &g](auto ...args) { return g(f(args...)); };
}
 
// Error: "function returning a function" from both g++-5.1.1 and clang 3.5:
auto compose1(const auto& f, const auto& g)
{
 return [&f, &g](auto ...args) { return g(f(args...)); };
}
 
auto f(const std::string s) { return s; }
auto g(const std::string s) { return s + ", World!"; }
 
int main()
{
 std::cout << compose0(f, g)("Hello") << '\n';
 std::cout << compose1(f, g)("Hello") << '\n';
}