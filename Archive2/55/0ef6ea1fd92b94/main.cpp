#include <stdio.h>
#include <string.h>
 
void do_foo (char *pc, char const **pcc) {
  *pc = 'C'; // #2: modifies a const object
}
 
int main (void) {
  const char c = 'c';
  char* pc;
  const char **pcc = &pc;  // #1: Not allowed
  *pcc = &c;
  do_foo(pc, &pc);
  return 0;
}
