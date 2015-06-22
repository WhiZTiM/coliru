#include<iostream>

int main() {
  unsigned long long result = 0;
  for(unsigned long long i=0; i < 100000000; i++)
    result += i * i;
  std::cout << result << '\n';
}
