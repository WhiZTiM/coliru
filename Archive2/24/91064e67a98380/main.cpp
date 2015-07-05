#include <stdio.h>
 
inline void foo() { printf("foo\n"); }
 
int main(void) {
    void (*f)() = &foo;
	f();
	// your code goes here
	return 0;
}