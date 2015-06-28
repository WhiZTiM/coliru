#include <cstdlib>
#include <iostream>
#include <string>

template <class GenFunc>
auto make_gen_from(GenFunc&& func);

template <class T, class GenFunc>
class Gen 
{
    GenFunc genfunc;

  public:
    explicit Gen(GenFunc func) 
      : genfunc(std::move(func)) 
    { } 
    
    T generate() 
    {   
      return genfunc();
    }   
    
    template <class Func>
    auto map (Func&& func)
    {
      return make_gen_from([gt=*this, 
                            func=std::forward<Func>(func)]() mutable { 
                              return func(gt.generate()); 
                          });
    }
    
    template <class UGen, class Zipper2>
    auto zip2(UGen&& ugen, Zipper2&& func)
    {
      return this->map(
                [ugen=std::forward<UGen>(ugen),
                 func=std::forward<Zipper2>(func)](auto&& t) mutable {
                    return func(std::forward<decltype(t)>(t), ugen.generate());
                });
    }
    
    
};

template <class GenFunc>
auto make_gen_from(GenFunc&& func)
{
  return Gen<decltype(func()), GenFunc>(std::forward<GenFunc>(func));
}

template <class T>
auto make_gen();

template <>  
auto make_gen<long int>()
{
  return make_gen_from([]() { return random(); }); 
}

template <>
auto make_gen<int>()
{
  return make_gen<long int>().map([](long int i) { return static_cast<int>(i); });
}

template <>
auto make_gen<bool>()
{
  return make_gen<long int>().zip2(make_gen<long int>(),
                                   [](long int i, long int j) { return (i-j) > 0; }); 
}

template <class Integer>
auto make_range_gen(Integer lo, Integer hi) 
{
  return make_gen<long int>().map(
           [lo, hi](long int x) { return static_cast<Integer>(lo + x % (hi - lo)); });
}

template <>
auto make_gen<std::string>()
{
  auto char_gen = make_range_gen(32, 127); // printable characters.
  auto length_gen = make_range_gen(1, 256);

  return make_gen<bool>().zip2(
                      length_gen,
                      [char_gen](bool empty, int length) mutable {
                        std::string str;
                        if(!empty)
                        {
                          str.reserve(length);
                          for(int i = 0; i < length; ++i)
                            str.push_back(char_gen.generate());
                        }
                        return str;
                      });
}

template <class T>
auto make_single_gen(T&& t)
{
    return make_gen_from([t=std::forward<T>(t)]() { return t; });
}

template <class T>
auto make_oneof_gen(std::initializer_list<T> list)
{
    return make_range_gen(0ul, list.size()).map([list](int idx) { return *(list.begin()+idx); }); 
}

auto fiboGen()
{
  int a = 0;
  int b = 1;
  return make_gen_from([a, b]() mutable {
                          int c = a;
                          a = b;
                          b = c+b;
                          return c;
                       });
}

bool random_bool1()
{
  return (random()-random()) > 0;
}

bool random_bool2()
{
  return make_gen<long int>()
           .zip2(make_gen<long int>(),
                 [](long int i, long int j) { return (i-j) > 0; })
           .generate();
}

int main()
{
  time_t t;
  time(&t);
  srandom(t);
  auto gen = make_gen<long int>();
  auto intgen   = make_gen<int>();
  auto uppergen = make_range_gen<char>('A', 'Z'+1);
  auto lowergen = make_range_gen<char>('a', 'z'+1);
  auto pairgen  = 
    uppergen.zip2(lowergen, 
                  [](char up, char low) { return std::make_pair(up, low); }); 
  auto stringgen = make_gen<std::string>();  
  auto same      = make_single_gen("same");
  auto oneofgen  = make_oneof_gen({"Moon", "Earth", "Sun", "Mars"});
  auto fibogen = fiboGen();
  
  std::cout << intgen.generate() << "\n"; 
  std::cout << uppergen.generate() << "\n"; 
  std::cout << lowergen.generate() << "\n"; 
  auto pair = pairgen.generate();
  std::cout << pair.first << " " << pair.second  << "\n";
  std::cout << stringgen.generate() << "\n";
  std::cout << same.generate() << "\n";
  std::cout << oneofgen.generate() << "\n";
  
  for(int i=0;i < 10; i++)
    std::cout << fibogen.generate() << " ";

  std::cout << std::endl;
  
  
  std::cout << "gen = "    << sizeof(gen) << " "
            << "intgen = " << sizeof(intgen) << " "
            << "uppergen = " << sizeof(uppergen) << " "
            << "lowergen = " << sizeof(lowergen) << " "
            << "pairgen = " << sizeof(pairgen) << " "
            << "stringgen = " << sizeof(stringgen) << " "
            << "fibogen = " << sizeof(fibogen) << " ";
}
