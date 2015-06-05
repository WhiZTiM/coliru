#include <iostream>
#include <string>
#include <vector>

int promoted(char);
int promoted(short);
int promoted(int);
long promoted(long);
long long promoted(long long);
double promoted(float);
double promoted(double);
long double promoted(long double);

int main()
{
    unsigned long long i = 0;
    std::cout << sizeof(i) << " " << sizeof(promoted(i);
}
