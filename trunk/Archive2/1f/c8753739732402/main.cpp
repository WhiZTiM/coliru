#include <iostream>
#include <regex>


int main (int argc, char *argv[]) {
  std::regex pattern("[a-z]+", std::regex_constants::icase);
  std::regex pattern2("excelsior", std::regex_constants::icase);
  std::string text = "EXCELSIOR";

  if (std::regex_match(text, pattern)) std::cout << "works" << std::endl;
  else std::cout << "doesn't work" << std::endl;

  if (std::regex_match(text, pattern2)) std::cout << "works" << std::endl;
  else std::cout << "doesn't work" << std::endl;

  return 0;
}