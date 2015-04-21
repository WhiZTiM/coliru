#include <string>
#include <iostream>

int main() {

   std::string A;
   A += (std::string){65, 66};
   std::cout << A;

}