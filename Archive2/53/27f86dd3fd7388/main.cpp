#include <stdio.h>

int ft_atoi(const char *str)
{
    int sign;
    int val;
    int nbr;

    sign = 1;
    val = 0;
    nbr = 0;
    
    while (*str)
    {
        if (!val && *str == '-')
        {
            sign = -1;
        }
        else if (*str >='0' && *str <='9')
        {
            nbr = (int) (*str - '0');
            val = (val * 10) + nbr;
        }
        ++str;
    }
    
    return (val * sign);
}


int main()
{
    printf("%d\n", ft_atoi("2464"));
    printf("%d\n", ft_atoi("-2464"));
    return 0;
}
