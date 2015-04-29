#include <iostream>

void f(int t[10][20]) { t[0][0] = 1; }

int main() {
    int table[10][20];
    table[0][0] = 0;
    f(table);
    std::cout << table[0][0] << "\n";
}

