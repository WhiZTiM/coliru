#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stdio.h>      /* printf */
#include <math.h>       /* sqrt */

int main() 
{   
   double a = 30;
   double b = 90;
   double c =70;
   double U = rand() / (double) RAND_MAX;
   double F = (c - a) / (b - a);
   if (U <= F)
      std::cout << a + sqrt(U * (b - a) * (c - a));
   else
      std::cout << b - sqrt((1 - U) * (b - a) * (b - c));

}