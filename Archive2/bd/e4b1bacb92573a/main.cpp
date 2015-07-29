#include <stdio.h>


int main()
{
    const char* input = "3.14 2.78 1.93";
    double a, b;
    int n = sscanf(input, "%lf %lf %lf", &a, &b);
    printf("%d %f %f %f\n", n, a, b);
    return 0;
}
