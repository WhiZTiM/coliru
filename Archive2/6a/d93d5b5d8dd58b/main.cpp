#include <stdio.h>
int main()
{
      int a, b, c, e, f, d;
  	a=-1;b=-2;c=-3;
  	d = c<b < a;
	e=a<(b<c);
	f = a > b >c; 
  	printf("c:%i, f:%i, g:%i,"d,f,f);
}