/* signal example */
#include <stdio.h>      /* printf */
#include <signal.h>     /* signal, raise, sig_atomic_t */
#include <stdlib.h>

void my_handler (int param)
{
  printf ("signaled is %d.\n",param);
}

int main ()
{
  signal (12345, my_handler);//

  raise(12345);
  
  printf ("aaaa\n");
  
  return 0;
}