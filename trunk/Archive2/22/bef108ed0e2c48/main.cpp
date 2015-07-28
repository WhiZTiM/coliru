#include <stdio.h>
#include <string.h>

int main(int argc, const char **argv)
{
    const char *binary = "1101110011111";
	int value = 0;
	int len = strlen(binary);
	int factor = 1;
	for (int i = len - 1; i >= 0; i--) {
    	value += (binary[i] - '0') * factor;
    	factor *= 2;
	}
	printf("%d\n", value);
	return 0;
}
