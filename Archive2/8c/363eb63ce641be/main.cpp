#include <iostream>

typedef unsigned long long ullong;
const int max_digit = 10;
ullong sticks_per_digit[max_digit+1] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};
ullong naive_matchstick(ullong num_sticks, bool allow_zero=false) {
    ullong result = 0;
    unsigned min_digit = (allow_zero ? 0 : 1);
    for(unsigned digit=min_digit; digit<max_digit; ++digit) {
        unsigned sticks_this_digit = sticks_per_digit[digit];
        if (num_sticks >= sticks_this_digit) {
            result += 1 + naive_matchstick(num_sticks-sticks_this_digit, true);
        }
    }
    if (allow_zero==false && num_sticks>=sticks_per_digit[0])
        ++result;
    return result;
}

int main() {
    for(int i=0; i<35; ++i) 
        std::cout << i << '-' << naive_matchstick(i) << '\n';
}