#include <stdio.h>
#include <math.h>
int main()
{
    double a = 3.14;
    while (a > -3.14)
    {
        double b = sin(a);
        printf("%f %f\n", a, b);
        a = a – 0.1;
    }
}
