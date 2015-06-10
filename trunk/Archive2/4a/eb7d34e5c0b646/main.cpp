#include <iostream>
using namespace std;

template<typename T>
void print(T &&number){
    cout<<"\n template \n";
}

int main() {
  int n=10;
  print(n);
  print(20);
}