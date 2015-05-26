#include <iostream>
 
void print(const char* str)
{
  std::cout << "length   = " << std::char_traits<char>::length(str) << '\n';
}

template <size_t SIZE>
void print(const char(&str)[SIZE])
{
  std::cout << "length[] = " << SIZE << '\n';
}

int main()
{
  print("foo");
  
  char a[] = {'f', 'o', 'o'};
  print(a);

  char b[] = {'f', 'o', 'o', '\0'};
  print(b);

  char c[] = "foo";
  print(c);
}  
