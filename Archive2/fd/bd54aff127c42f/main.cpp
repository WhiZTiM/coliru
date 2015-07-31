#include <stdio.h>

int lcss(const char *s1, int len) 
{
    if (len <= 1)
        return 0;
    
    const char *term = s1 + len;
    const char *s2 = s1 + 1;
    int len1 = 1, len2 = 1;; 
    int max_len = 0;
    
    while (s1 < term)
    {
        start2 = end1;
        if (*s1 == *s2)
        {
            temp_s1 = s1;
            temp_s2 = s2;
            int local_max = 0;
            while (temp_s1 < end1 && *temp_s1 == *temp_s2)
            {
                ++local_max;
                ++temp_s1;
                ++temp_s2;
            }
            
            if (local_mx > max_len)
                max_len = local_max;
            
            s1 = temp_s1;
            s2 = temp_s2;
        }
        ++s1;
        ++s2;
    }
    
    return max_len;
}

int main(int argc, const char* argv[]) 
{
    printf(lcss("banana"));
}


