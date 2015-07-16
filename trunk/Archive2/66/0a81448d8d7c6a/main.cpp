#include <iostream>
#include <cstdio>
#include <cstdlib>
 
int main()
{
    FILE *fpSQLFile = NULL;
    char l_chSQL[1024] = {0};
	fpSQLFile = fopen("","r");
	fgets(l_chSQL, iMaxSQLLen, fpSQLFile);
    printf("%s",);
}