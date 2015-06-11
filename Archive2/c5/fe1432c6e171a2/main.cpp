#include <iostream>
using namespace std;

void print(int const &number){
    cout<<"\n int const & \n";
}

int main() {
  int n=10;
  print(n);
  print(20);
}