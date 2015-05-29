#include <stdio.h>
#include <stdarg.h>
#include <time.h>

void log_base(int level, const char* fmt, va_list args)
{
    printf("[%d]: ", level);
    vprintf(fmt, args);
}
 
void log(int level, const char* fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);
    log_base(level, fmt, ap);
    va_end(ap);
}


 
int main(void)
{
    log(42, "Logging, %d, %d, %d", 1, 2, 3);
}