#include <vector>
#include <string>
#include <iostream>
 
int main() 
{
  std::vector<std::string> words(5, "Mo");
  for(auto s:words){
    std::cout << s << std::endl;
  }
}