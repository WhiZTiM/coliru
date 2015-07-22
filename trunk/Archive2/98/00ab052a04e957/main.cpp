#include "stdio.h"

int ft_atoi(const char *str)
{
    int sign;
    int val;
    int nbr;
    const char *p;

    sign = 1;
    val = 0;
    nbr = 0;
    
    for (p = str; *p; ++p)
    {
        if (!val & *p=='-')
        {
            sign = -1;
        }
        else
        {
            nbr = (int) (*p - '0');
            val = (val * 10) + nbr;
        }
    }
    
    return (val * sign);
}


int main()
{
    printf("%d\n", ft_atoi("2464"));
    printf("%d\n", ft_atoi("-2464"));
    return 0;
}
