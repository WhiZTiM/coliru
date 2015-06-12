#include <stdio.h>
#undef NDEBUG
//#define NDEBUG

void swap(int **r,int **s) {
  int *t;
  t=*r;
#ifndef NDEBUG
  printf(" r:%p  s:%p\n", r, s);
  printf("before: *r:%p *s:%p  t:%p\n", *r, *s, t);
#endif
  *r=*s;
  *s=t;
#ifndef NDEBUG
  printf("after:  *r:%p *s:%p\n", *r, *s);
#endif
}
int main(void) {
  int a=1,b=2,*p,*q;
  p=&a;
  q=&b;
#ifndef NDEBUG
  printf("&a:%p &b:%p  p:%p  q:%p\n", &a, &b, p, q);
  printf("&p:%p &q:%p\n", &p, &q);
#endif
  swap(&p,&q);
  printf("%d,%d\n",*p,*q);
  return 0;
}
