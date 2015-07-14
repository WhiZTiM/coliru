#include <iostream>
#include <stdlib.h>

using namespace std;

void randtest(const int count)
{
  for(int i = 0; i < count; i++)
  {
    cout << rand() % 100 + 1 << " ";
  }

  cout << "\n";
}

int main()
{
  unsigned int seed;
  const int count = 5;

  seed = 1;    
  srand (seed);
  cout << "种子 = " << seed << ", 第一次: ";
  randtest(count);
    
  srand (seed);
  cout << "种子 = " << seed << ", 第二次: ";
  randtest(count);

  cout << "----------------------------------\n";
  
  seed = 2;
  srand (seed);
  cout << "种子 = " << seed << ", 第一次: ";
  randtest(count);

  srand (seed);
  cout << "种子 = " << seed << ", 第二次: ";
  randtest(count);
  
  cout << "----------------------------------\n";

  seed = 1;    
  srand (seed);
  cout << "种子 = " << seed << ", 第一次: ";
  randtest(count);
    
  cout << "种子 = " << seed << ", 第二次: ";
  randtest(count);
}