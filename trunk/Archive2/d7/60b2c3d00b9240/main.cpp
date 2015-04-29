#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//http://stackoverflow.com/a/1001373/977038
int is_big_endian(void)
{
    union {
		int i;
		char c[4];
	} bint = { 0x01020304 };

	return bint.c[0] == 1;
}
int main(int argc, char **argv)
{
	volatile int modified;
	char buffer[64];
	if (strcmp(argv[1], "CHECK") == 0)
	{
		size_t arg_size = (char *)&modified - (char *)buffer  + 1;
		char *arg = (char *)malloc(sizeof(char)*(arg_size));
		memset(arg, 'X', arg_size - 1);
		arg[arg_size - 1] = 0;
		if (is_big_endian())
			printf("Your argument should be %sabcd\n", arg);
		else
			printf("Your argument should be %sdcba\n", arg);
		exit(0);
	}

	modified = 0;
	strcpy(buffer, argv[1]);

	if (modified == 0x61626364) {
		printf("you have correctly got the variable to the right value\n");
	}
	else {
		printf("Try again, you got 0x%08x\n", modified);
	}
}