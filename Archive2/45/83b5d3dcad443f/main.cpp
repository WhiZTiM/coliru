#include <type_traits>
#include <queue>

int f(int i)
{
   return i;
}

template<class F, class T>
auto ExecFunc(F f, T arg) -> std::queue<typename std::result_of<F(T)>::type>
{
    std::queue<typename std::result_of<F(T)>::type> foo;
    foo.push(f(arg));
    return foo;
}

int main() {
   auto a = ExecFunc(f, 3);
   return 0;
}