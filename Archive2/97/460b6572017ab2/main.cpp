#include <iostream>
#include <string>
#include <vector>

char* int_to_str(int n) {
    static int digits = 0;
    digits++;
    if (n) {
        char digit = n % 10;
        int current = digits;
        char *result = int_to_str(n / 10);
        result[digits - current - 1] = '0' + digit;
        if (current == 1) {
            digits = 0;
        }
        return result;
    } else {
        char *result = new char[digits + 1];
        result[digits] = '\0';
        return result;
    }
}

int main()
{
    printf("%s\n", int_to_str(11232313));
    printf("%s\n", int_to_str(98712312));
    return 0;
}
