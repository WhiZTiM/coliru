#include <string>
#include <iostream>
#include <tuple>

auto combine = [](auto... funcs)
{
    return [=](auto... args)
    {
        return std::make_tuple(funcs(args...)...);
    };
};

int main ()
{
    const auto fn = combine(
      [](int a, double)
      {
          return a;
      },
      [](int, double b)
      {
          return "Hello: " + std::to_string(b);
      });
           
    const auto r = fn(1, 2.2);
    std::cout << std::get<0>(r) << ", " << std::get<1>(r) << std::endl;
}
