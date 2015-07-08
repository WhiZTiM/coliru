#include <codecvt>  
#include <string>  
#include <locale>  
#include <iostream>  

using namespace std;  

int main(int argc, char const *argv[])
{
  wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t>
                                                convert;

  u16string utf16 = u"\ub098\ub294\ud0dc\uc624";

  cout << hex << "UTF-16\n\n";
  for (char16_t c : utf16)
    cout << "[" << c << "] ";

  string utf8 = convert.to_bytes(utf16);

  cout << "\n\nUTF-16 to UTF-8\n\n";
  for (unsigned char c : utf8)
    cout << "[" << int(c) << "] ";
  cout << "\n\nConverting back to UTF-16\n\n";

  utf16 = convert.from_bytes(utf8);

  for (char16_t c : utf16)
    cout << "[" << c << "] ";
  cout << endl;
}