#include <iostream>
#include <string>
#include <vector>

float * methodeB() {
  float * y = new float[3];
  //wir machen coolen scheiss
  return y;
}


void methodeA() {
  float * x[3];
  
  
  for(int i=0; i<3; i++) x[i] = methodeB();
  
  //irgendwas anderes
  
  //gibt alles in x frei
  for(int i=0; i<3; i++) delete[] x[i];
}
 

int main(){
   std::cout <<"FOO" <<std::endl;
   methodeA(); 
}