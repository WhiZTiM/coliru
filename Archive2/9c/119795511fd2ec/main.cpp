#include <functional>
#include <type_traits>
#include <iostream>

using namespace std;

void log(const string& s) { cout << "log(string)\n"; }
template <class ... Args>
auto log(const char *ptr, Args ... args)  -> typename std::enable_if< sizeof...(Args) != 0, void>::type
{
     cout << "log(const char*)\n";
}



int main()
{
      log("hello");
      log("Hello", 5, 1.0);

}