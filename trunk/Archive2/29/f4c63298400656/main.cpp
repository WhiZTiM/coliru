#include <iostream>
#include <csetjmp>
 
std::jmp_buf jump_buffer;
 
void a(int count) 
{
    std::cout << "a(" << count << ") called\n";
    std::longjmp(jump_buffer, count+1);  // setjump() will return count+1
}
 
int main()
{
    int count = 0; // local variables must be volatile for setjmp
    if (setjmp(jump_buffer) != 9) {
        a(count++);  // This will cause setjmp() to exit
    }
}