#include <string>
#include <locale>
#include <codecvt>

std::wstring a2w(const std::string& s)
{
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wcharconv;
  try
  {
    return wcharconv.from_bytes(s);
  }
  catch(const std::range_error&)
  {
    return wcharconv.from_bytes(s.substr(0, wcharconv.converted()));
  }
  return {};
}

std::string w2a(const std::wstring& w)
{
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wcharconv;
  try
  {
    return wcharconv.to_bytes(w);
  }
  catch(const std::range_error&)
  {
    return wcharconv.to_bytes(w.substr(0, wcharconv.converted()));
  }
  return {};
}

#include <map>
#include <iostream>

int main(int argc, char* argv[])
{
  static const std::map<std::string, std::string> tests = {
      {"Valid ASCII", "a"},
      {"Valid 2 Octet Sequence", "\xc3\xb1"},
      {"Invalid 2 Octet Sequence", "\xc3\x28"},
      {"Invalid Sequence Identifier", "\xa0\xa1"},
      {"Valid 3 Octet Sequence", "\xe2\x82\xa1"},
      {"Invalid 3 Octet Sequence (in 2nd Octet)", "\xe2\x28\xa1"},
      {"Invalid 3 Octet Sequence (in 3rd Octet)", "\xe2\x82\x28"},
      {"Valid 4 Octet Sequence", "\xf0\x90\x8c\xbc"},
      {"Invalid 4 Octet Sequence (in 2nd Octet)", "\xf0\x28\x8c\xbc"},
      {"Invalid 4 Octet Sequence (in 3rd Octet)", "\xf0\x90\x28\xbc"},
      {"Invalid 4 Octet Sequence (in 4th Octet)", "\xf0\x28\x8c\x28"},
      {"Valid 5 Octet Sequence (but not Unicode!)", "\xf8\xa1\xa1\xa1\xa1"},
      {"Valid 6 Octet Sequence (but not Unicode!)", "\xfc\xa1\xa1\xa1\xa1\xa1"}};

  std::string s;
  std::wstring w;
  for(const auto& e : tests)
  {
    s = e.second;
    std::cout << e.first << ": '" << e.second << "', converted: '";
    w = a2w(s);
    std::wcout << w;
    s = "";
    s = w2a(w);
    std::cout << "', and back: '" << s << "'" << std::endl;
  }

  return 0;
}
