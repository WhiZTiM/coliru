#include <iostream>
#include <stdlib.h>

using namespace std;


void randtest(int* output, int count)
{
  for(int i = 0; i < count; i++)
  {
    output[i] = rand() % 100 + 1;
    cout << output[i] << " ";
  }

  cout << "\n";
}

int main()
{
  unsigned int seed;
  const int count = 5;
  int num[count];

  seed = 1;    
  srand (seed);
  cout << "种子 = " << seed << ", 第一次: ";
  randtest(num, count);
    
  srand (seed);
  cout << "种子 = " << seed << ", 第二次: ";
  randtest(num, count);

  cout << "----------------------------------\n";
  
  seed = 2;
  srand (seed);
  cout << "种子 = " << seed << ", 第一次: ";
  randtest(num, count);

  srand (seed);
  cout << "种子 = " << seed << ", 第一次: ";
  randtest(num, count);
  
  cout << "----------------------------------\n";

  seed = 1;    
  srand (seed);
  cout << "种子 = " << seed << ", 第一次: ";
  randtest(num, count);
    
  cout << "种子 = " << seed << ", 第二次: ";
  randtest(num, count);

}