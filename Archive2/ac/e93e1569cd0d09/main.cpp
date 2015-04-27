#include <algorithm>

int checkForSimilar(int arraya[], int arrayb[], int a, int b)
{
  if (a != b) 
   return 0;
  
  std::sort(arraya, arraya + a);
  std::sort(arrayb, arrayb + b);
  
  for (int index = 0; index < a; ++index) 
  {
    if (arrarya[index] != arraryb[index]) 
      return 0;
  }
  return 1;
}