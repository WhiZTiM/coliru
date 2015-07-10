
#include <iostream>

inline void cpy(char* p, const char* q)
{
 while (*p++ = *q++) ;
}


int main(int argc, char *argv[])
{
    char chars[] = "abcdef";
	char charRecv[sizeof(chars)+1];
 
	char *it_start	= &chars[0];
    char *it_end 	= &charRecv[0];
 
    while(*it_end++ = *it_start++);
 
	cout << charRecv << endl;
	return 0;

}