#include <iostream>
#include <sstream>


void writeToStream(std::stringstream& sstr){
   sstr << "Hello World";
}

int main(){
   std::stringstream sstr;
   writeToStream(sstr);
   std::cout << sstr.str();
}