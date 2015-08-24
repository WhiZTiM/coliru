#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* string_concat(char* s1, char *s2);
char* safe_string_concat(char* s1, char *s2);
int newdate(int date1, int numMonths);

int main()
{
    //printf("Processed string is: %s \n", string_concat("pavan", "raj"));
    printf("Processed string is: %s \n", safe_string_concat("pavan", "raj"));
    printf("Newdate is: %d\n", newdate(201409, 5));
    printf("Newdate is: %d\n", newdate(201409, -11));
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

int newdate(int date1, int numMonths)
{
    int year = date1/100;
    int month = date1 - year*100;
    int adjustedMonth = month + numMonths;
    // some more coding needs to be done if months is a larger negative number..add a while loop!!!
    if (adjustedMonth < 0)
    {
        year = year -1;
        adjustedMonth += 12;
    }
    int newyear = year + adjustedMonth/12;
    int newMonth = adjustedMonth % 12;
    return newyear*100 + newMonth;
}