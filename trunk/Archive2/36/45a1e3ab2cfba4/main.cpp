#include <iostream>
#include <iterator>
#include <utility>
#include <functional>

template<typename Function, typename... Args>
auto toStdFun(Function&& fun, Args&&...args)
{
    static_assert(std::is_same<decltype(std::forward<Args>(args))..., Args&&...>::value, "fail!!");
    using retType = decltype(fun(std::forward<Args>(args)...));

    return std::function<retType(decltype(std::forward<Args>(args))...)>(fun);

}

int main()
{
    toStdFun([] (int) {}, 0);

}