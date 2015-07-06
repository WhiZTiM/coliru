#include <iostream>
struct my_string {
   my_string& operator=(char const& c) 
   {
      std::cout << "operator=\n";
      std::cout << c << "\n";
      return *this;
   } 
};
int main() {
    int i = 1000;
    my_string s;
    s = i; // ok, but value of `s` is not 1000!, char overflow instead.
}