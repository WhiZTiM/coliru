#include <iostream>
#include <regex>
#include <string>

int main(int argc,char *argv[]){

  std::string text = argv[1];

  std::regex rx(".*\\.h5$");
  bool found = std::regex_search(text.c_str(),rx);

  std::cout << text << std::endl;
  std::cout << "res: " << found << std::endl;


}