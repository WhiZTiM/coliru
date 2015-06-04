#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int     strchr_count(const char *str, char c)
{
    int     ret;
    int     i;

    ret = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            ret++;
        i++;
    }
    return (ret);
}

char rot(char c, int n)
{
    return (c + n) % 26;
}

char    *one(const char *str, int n)
{
    char    *out;
    int     i;
    int     j;
    
    assert(str != NULL);
    out = (char*)malloc(sizeof(char) * (strlen(str) - strchr_count(str, ' ') + 1));
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
        {
            if (str[i] >= 'a' && str[i] <= 'z')
                out[j] = rot(str[i] - 'a', n) + 'A';
            else if (str[i] >= 'A' && str[i] <= 'Z')
                out[j] = rot(str[i] - 'A', n) + 'a';
            else
                out[j] = str[i];
            j++;
        }
        i++;
    }
    return (out);
}

int     max_len(const char *list[])
{
    unsigned int        ret;
    int                 i;
    
    ret = 0;
    i = 0;
    while (list[i] != NULL)
    {
        if (strlen(list[i]) > ret)
            ret = strlen(list[i]);
        i++;
    }
    return (ret);
}

int     bigger(char a, char b)
{
    if (a >= 'A' && a <= 'Z')
        a = a - 'A' + 'a';
    if (b >= 'A' && b <= 'Z')
        b = b - 'A' + 'a';
    if ((!isalnum(a) && isalnum(b)) || (isdigit(a) && isalpha(b)))
        return (0);
    if ((isalnum(a) && !isalnum(b)) || (isalpha(a) && !isalpha(b)))
        return (1);
    return (a > b);
}

char    get_max(const char *list[], unsigned int n)
{
    char    ret;
    int     i;
    
    ret = 0;
    i = 0;
    while (list[i] != NULL)
    {
        if (strlen(list[i]) > n && bigger(list[i][n], ret))
            ret = list[i][n];
        i++;
    }
    return (ret);
}

char    *two(const char *list[])
{
    char    *out;
    int     i;
    int     max;
    
    i = 0;
    max = max_len(list);
    out = (char *)malloc(sizeof(char) * (max + 1));
    while (i <= max)
    {
        out[i] = get_max(list, i);
        i++;
    }
    return (out);
}

void    shuffle(int *array, unsigned int len)
{
    unsigned int    i;
    unsigned int    j;
    int             tmp;

    if (len <= 1)
        return;
    i = 0;
    while (i < len) 
    {
        j = i + rand() % (len - i);
        tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
        i++;
    }
}

int     *three(unsigned int len)
{
    int             *out;
    unsigned int    i;
    
    out = (int *)malloc(sizeof(int) * len);
    i = 0;
    while (i < len)
    {
        out[i] = i + 1;
        i++;
    }
    shuffle(out, len);
    return (out);
}

int main()
{
    const char  *example[] = {"Je_teste cette phrase.", "Je teste 2 fois"};

    std::cout << one("J'aime la programmation!", 3) << std::endl;
    std::cout << two(example) << std::endl;
    three(10);
    return (0);
}