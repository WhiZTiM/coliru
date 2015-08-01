#include <iostream>

int operator""_x(unsigned long long int x) { return x; }

int main() { operator""_x; }