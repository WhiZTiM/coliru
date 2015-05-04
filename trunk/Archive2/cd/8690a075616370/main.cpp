//http://stackoverflow.com/questions/16017767/c11-initializer-lists-on-variadic-templates-parameters-why-isnt-this-workin
#include <iostream>
using namespace std;


template<class T> void some_function(T var)
{
   cout << var << endl;
}

template<size_t N> void some_function(const char (&var)[N])
{
   cout << "string[" << N << "]=" << var << endl;
}


struct expand_aux {
    template<typename... Args> expand_aux(Args&&...) { }
};

template<typename... Args> inline void expand(Args&&... args) 
{
   //bool b[] =      {(some_function(std::forward<Args>(args)),true)...}; // This output is 42, "true", false and is correct
   // expands to
     bool b[] = {
                (some_function(int(42)),    true)
                ,
                (some_function(("true")),   true)
                ,
                (some_function(bool(false)),true)
                };
   cout << "other output" << endl;
   //expand_aux  temp3 {(some_function(std::forward<Args>(args)),true)...}; // This output isn't correct, it is false, "true", 42
     expand_aux  temp3 {
                (some_function(int(42)),    true)
                ,
                (some_function(("true")),   true)
                ,
                (some_function(bool(false)),true)
                };
   static auto temp4 = temp3;
   static auto b4 = b;
   cout << "sizeof(b4)=" << sizeof(b4) << endl;
}

int main()
{
   expand(42, "true", false);

   return 0;
}