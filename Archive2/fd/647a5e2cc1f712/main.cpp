#include <iostream>
#include <regex>


int main (int argc, char *argv[]) {
  std::vector<std::regex>
    patterns = {
      std::regex{"[a-z]+", std::regex_constants::icase},
      std::regex{"[A-Z]+", std::regex_constants::icase},
      std::regex{"[a-z]+SIOR", std::regex_constants::icase},
      std::regex{"[A-Z]+SIOR", std::regex_constants::icase},
      std::regex{"EXCELSIOR", std::regex_constants::icase}
  };
  
  std::string
    text = "excelsior";

  for(auto &&pattern : patterns){
      
    if (std::regex_match(text, pattern)) std::cout << "works" << std::endl;
    else std::cout << "doesn't work" << std::endl;
  }

  return 0;
}