#include <stdio.h>
int main()
{
    int a = 16580;
    int b = 19019;
    
    for (int i = a; i < b+1; )
    {
        int step = 1;
        while ((i + step * 10 <= b + 1)  &&  i % (step * 10) == 0)
          step *= 10;
        
        printf("%d\n", i / step);
        i += step;
    }
        
    return 0;
}