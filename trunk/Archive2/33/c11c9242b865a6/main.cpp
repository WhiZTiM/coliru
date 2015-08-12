#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

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

int fib(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

std::string table[4][10] = {
    {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
    {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
    {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
    {"", "M", "MM", "MMM", "MMMM", "MMMMM", "", "", "", ""}
};

std::string roman(int n) {
    static int level = 0;
    if (n) {
        int current = level++;
        int digit = n % 10;
        std::string result = roman(n / 10);
        result += table[current][digit];
        level = current;
        return result;
    }
    return std::string("");
}

void repeated(int n) {
    int digits[10] = {};
    while (n) {
        int digit = n % 10;
        digits[digit]++;
        n /= 10;
    }
    for (int i = 0; i < 10; i++) {
        std::cout << i << ": " << digits[i] << std::endl;
    }
}

void sum_digits(int n) {
    int sum = 0;
    while (n) {
        sum += n % 10;
        n /= 10;
    }
    std::cout << sum << std::endl;
}

std::string repeated_chars(std::string a, std::string b)
{
    std::string result = "";
    std::unordered_map<char, int> h;
    for (char &c : a) {
        h[c]++;
    }
    for (char &c : b) {
        if (h[c] > 0) {
            result += c;
            h[c] = 0;
        }
    }
    return result;
}

int main()
{
    std::cout << repeated_chars("aabbccddd", "abbbbcccc") << std::endl;
    //sum_digits(12345);
    //printf("%s\n", int_to_str(11232313));
    //printf("%s\n", int_to_str(98712312));
    
    //std::cout << roman(10) << std::endl;
    //std::cout << roman(39) << std::endl;
    //std::cout << roman(49) << std::endl;
    //std::cout << roman(89) << std::endl;
    
    //for(int i = 0; i < 10; i++) {
    //    std::cout << fib(i) << ' ';
    //}
    //std::cout << std::endl;
    return 0;
}
