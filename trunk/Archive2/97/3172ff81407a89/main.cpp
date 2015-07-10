#include <iostream>

short short_var1 = 4000;
short short_var2 = 5000;
short short_var3 = 4000;
long long_var1 = 4000;
long long_var2 = 5000;
long long_var3 = 4000;

#define K1 0
#define K2 20000
#define K3 40000

// long 2147483647;
// short 65535;

// numerador 260000000
// denominador 13000
// resultado 20000 (K2)

int main(void) {
    short short_output;
    long long_output;
  
    long_output = (long_var1 * K1 + long_var2 * K2 + long_var3 * K3) / (long_var1 + long_var2 + long_var3);

    std::cout << long_output << std::endl;


    short_output = ((long)short_var1 * K1 + (long)short_var2 * K2 + (long)short_var3 * K3) / ((long)short_var1 + (long)short_var2 + (long)short_var3);

    std::cout << short_output << std::endl;


    short_output = (short_var1 * K1 + short_var2 * K2 + short_var3 * K3) / (short_var1 + short_var2 + short_var3);

    std::cout << short_output << std::endl;

    return 0;
}
