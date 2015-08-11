#include <stdio.h>

void foo(int m, int n, int (*a)[m])
{
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            a[i][j] = 5;
}

int main()
{
    int m = 20, n = 10;
    int a[m][n];
    
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            a[i][j] = 0;
            
    foo(m, n, a);
    
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf("%d ", a[i][j]);
        printf("\n");
    }

}