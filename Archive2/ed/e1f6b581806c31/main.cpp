#include <iostream>
#include <regex>
#include <string>

int main () {
  std::regex e ("(\\+|\\-)((\\d)+)((years)|(months)|(weeks)|minutes|seconds)");
  std::string str("+50years-4months+3weeks+5minutes");
  std::sregex_iterator next(str.begin(), str.end(), e);
  std::sregex_iterator end;
  while (next != end) {
    std::smatch match = *next;
    std::cout << "Expression: " << match.str() << "\n";
    std::cout << "  mathOperator : " << match[1] << std::endl;
    std::cout << "  value        : " << match[2] << std::endl;
    std::cout << "  timeUnit     : " << match[4] << std::endl;
    ++next;
  }
}