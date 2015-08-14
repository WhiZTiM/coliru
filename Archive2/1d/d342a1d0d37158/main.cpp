// Example program
// Prints a UTF-8 string to stdout
// Fails miserably on non-BMP characters (throws std::range_error)!

#include <ciso646>
#include <iostream>
#include <codecvt>
#include <locale>
#include <string>

void print( const char32_t* s )
{
  std::u32string u = s;
  std::cout << std::wstring_convert <std::codecvt_utf8 <char32_t>, char32_t> ().to_bytes( u ) << std::endl;
}

int main()
{
  std::cout << "trial 1: " << std::flush;
  print( U"\U0002A6A5" );  // BMP Chinese character found online
  
  std::cout << "trial 2: " << std::flush;
  print( U"\U001F1800" );  // non-BMP left arrow "<--"
}