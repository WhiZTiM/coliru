#include <iostream>
#include <string>
#include <vector>

class C {
      public:
    const static int n = 1;
    int v[n];    
    };

int main(){
     std::cout << "ciao";
     int C::v[n];
     return 0;
    }