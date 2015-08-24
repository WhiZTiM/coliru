#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* string_concat(char* s1, char *s2);
char* safe_string_concat(char* s1, char *s2);

int main()
{
    //printf("Processed string is: %s \n", string_concat("pavan", "raj"));
    printf("Processed string is: %s \n", safe_string_concat("pavan", "raj"));
    return 0;
}

char* string_concat(char* s1, char *s2)
{
    char *buf;
    const char *del = "~" ;
    char *ret;
    buf = (char*) malloc(sizeof(s1)+sizeof(s2)+1);
    strcpy(buf,del);
    strcat(buf,s1);
    strcat(buf,del);
    strcat(buf,s2);
    strcat(buf,del);
    ret = strdup(buf);
    free(buf);
    return ret;
}

char* safe_string_concat(char* s1, char *s2)
{
    const char *del = "~" ;
    static char buf[1000];
    strcpy(buf,del);
    strcat(buf,s1);
    strcat(buf,del);
    strcat(buf,s2);
    strcat(buf,del);
    return buf;
}