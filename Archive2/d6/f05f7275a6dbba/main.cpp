#include <string>
#include <iostream>
 
void print(std::string::size_type n, std::string const &s)
{
  if(n == std::string::npos)
    std::cout << "not found\n";
  else
    std::cout << "found: " << s.substr(n) << '\n';
}
 
int main()
{
  std::string::size_type n;
  std::string const s = "This is a string";
 
  // поиск в обратном направлении от начала строки
  n = s.rfind("is");
  print(n, s);
  // поиск в обратном направлении с позиции 4
  n = s.rfind("is", 4);
  print(n, s);
  // поиск единственного символа
  n = s.rfind('s');
  print(n, s);
  // поиск единственного символа
  n = s.rfind('q');
  print(n, s);
}