#include <iostream>
#include <type_traits>

auto gL = 
    [](auto&& func, auto&&... params)
        -> std::enable_if_t<not std::is_same<void,
                                             decltype(std::forward<decltype(func)>(func)(std::forward<decltype(params)>(params)...))
                                            >{},
                            decltype(std::forward<decltype(func)>(func)(std::forward<decltype(params)>(params)...))
                           >
    {
        return std::forward<decltype(func)>(func)(
            std::forward<decltype(params)>(params)...); 
    };
    
int main() {
    gL([](const char * s){std::cout << s << '\n'; return 5;}, "foo");
	gL([](const char * s){std::cout << s << '\n'; return;}  , "bar");   // this one gets SFINAE'd out
}
